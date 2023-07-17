#include "Renderer.h"

Renderer::Renderer() {
}
Renderer::~Renderer() {
}


namespace Utils {
	static glm::ui8_tvec4 converttoRGBA(glm::vec4& color) {

		glm::ui8_tvec4 c;

		c.r = (uint8_t)(color.r * 255.0f);
		c.g = (uint8_t)(color.g * 255.0f);
		c.b = (uint8_t)(color.b * 255.0f);
		c.a = (uint8_t)(color.a * 255.0f);

		return c;
	}

	glm::vec3 Randomoffset1(float from, float to) {
		static float range_from = from;
		static float range_to = to;

		static std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());

		static std::uniform_real_distribution<float> distr(range_from, range_to);

		glm::vec3 offset(distr(generator), distr(generator), distr(generator));

		return offset;
	}

	glm::vec3 Randomoffset2(float from, float to) {
		static float range_from = from;
		static float range_to = to;

		static std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());

		static std::uniform_real_distribution<float> distr(range_from, range_to);

		glm::vec3 offset(distr(generator), distr(generator), distr(generator));

		return offset;
	}

	bool Inrange(float value, float low, float high) {
		if (value > low && value < high) {
			return true;
		}
		return false;
	}

	glm::vec4 Lerp(const Ray& ray, glm::vec3 start, glm::vec3 end) {
		const float value = ray.Direction.y;

		float t = 0.5f + (value * 0.5f);

		/// Calculate linear color gradient using linear interpolation
		glm::vec4 lineargradient = glm::vec4((1 - t) * start + t * end, 1.0f);

		return lineargradient;
	}
	void printSpec(const std::vector<Sphere>& SphereList) {
		std::cout << "Sphere Count => " << SphereList.size();
	}
}

glm::ui8_tvec4 Renderer::GammaCorrection(glm::vec4 color) {

	glm::vec4 c{0.0f};

	float scale = 1.0f / (float)renderScene->SampleCount;

	c.r = glm::sqrt(c.r * scale);
	c.g = glm::sqrt(c.g * scale);
	c.b = glm::sqrt(c.b * scale);

	return color;
}

void Renderer::Init(Raether& rae, const Scene& scene, Camera& camera) {
	raeObj = &rae;
	renderCam = &camera;
	renderScene = &scene;
}

void Renderer::Render(const Scene& scene, Camera& camera) {

	int width = renderCam->GetViewPortWidth();
	int height = renderCam->GetViewPortHeight();

	PixelData.resize(width * height);
	AccumPixelData.resize(width * height);

	if (FrameCount == 1) {
		/// Reset the Accumulate ImgaeBuffer
		memset(&AccumPixelData[0], 0, width * height * sizeof(glm::vec4));
	}

	else if (FrameCount < renderScene->SampleCount) {

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				glm::vec4 color = PerPixel(x, (height - 1) - y);

				/// Accumulate the color
				AccumPixelData[x + y * width] += color;

				glm::vec4 accumColor = AccumPixelData[x + y * width];

				/// Balancing the brightness 
				accumColor /= (float)FrameCount;

				accumColor = glm::clamp(accumColor, glm::vec4(0.0f), glm::vec4(1.0f));

				/// Store the color data
				PixelData[x + y * width] = GammaCorrection(Utils::converttoRGBA(accumColor));
			}
		}
		/// Draw the color using SDL
		raeObj->raeDrawPix(width, height, PixelData);
	}
	if (FrameCount <= renderScene->SampleCount) {
		FrameCount++;
	}
}

glm::vec4 Renderer::PerPixel(int x, int y) {

	Ray ray;
	ray.Origin = renderCam->GetPosition();
	ray.Direction = renderCam->GetRayDirection()[x + y * renderCam->GetViewPortWidth()] + Utils::Randomoffset1(-0.001f, 0.001f);

	Hitrec hitrecord;

	// Initialize the rayColor as white background
	glm::vec4 rayColor = glm::vec4(white, 1.0f);

	glm::vec4 incomingLight = glm::vec4(black, 1.0f);

	for (int i = 0; i < renderScene->Bounces; i++) {

		if (Hittable(ray, renderScene->SphereList, hitrecord) == false) {

			/*glm::vec4 SkyColor = Utils::Lerp(ray, white, blue);
			incomingLight += SkyColor * rayColor;*/

			break;
		}

		const Sphere& sphere = renderScene->SphereList[hitrecord.Hitobjindex];
		const Material& mat = renderScene->Materials[sphere.MatIndex];

		glm::vec3 emittedLight = mat.EmissionColor * mat.EmissionStrength;
		incomingLight += glm::vec4(emittedLight, 1.0f) * rayColor;
		rayColor = rayColor * glm::vec4(mat.Albedo, 1.0f);

		ray.Origin = hitrecord.Hitpoint + hitrecord.Surfacenormal * 0.0001f;
		ray.Direction = glm::reflect(ray.Direction + mat.Roughness * Utils::Randomoffset2(-1.0f, 1.0f), hitrecord.Surfacenormal);
	}
	 
	return incomingLight;
}

bool Renderer::Hittable(const Ray& ray, const std::vector<Sphere>& SphereList, Hitrec& hitrecord) {

	float closestHit = 101.0f; // hit out of range
	float t_min = 0.0f; // minimum hit distance
	float t_max = 100.0f; // maximum hit distance

	int loopCount = 0;

	int closestSphereIDX = -1;

	glm::vec3 hitpoint = glm::vec3(0.0f);

	glm::vec3 origin = glm::vec3(0.0f);

	for (auto& sphere : SphereList) {

		/// check the hit

		/// Sphere Equation
		/// 
		/// (bx^2 + by^2 + bz^2)t^2 + 2 ( (ax*bx + ay*by + az*bz) + (ax^2 + ay^2 + az^2) - r^2 = 0
		// a = camera origin (ax, ay, az)
		// b = ray direction (bx, by, bz)
		// t = hit distance
		// A , B , C = sphere origin
		// r = sphere radius

		glm::vec3 neworigin = ray.Origin - sphere.SphereOrigin;

		float a = glm::dot(ray.Direction, ray.Direction); // (bx^2 + by^2 + bz^2)
		float b = 2.0f * (glm::dot(neworigin, ray.Direction)); // 2 ((ax * bx + ay * by + az * bz)
		float c = glm::dot(neworigin, neworigin) - sphere.Radius * sphere.Radius; // (ax^2 + ay^2 + az^2) - r^2

		float discriminant = (b * b) - (4.0f * a * c);

		/// Calculate if the ray hits the sphere or not
		if (discriminant >= 0.0f) {

			float HitDist = (-b - std::sqrt(discriminant)) / (2.0f * a); // near hit distance

			if (loopCount == 0 && Utils::Inrange(HitDist, t_min, t_max)) {
				closestHit = HitDist;
				closestSphereIDX = loopCount;
			}
			else if (HitDist < closestHit && Utils::Inrange(HitDist, t_min, t_max)) {
				closestHit = HitDist;
				closestSphereIDX = loopCount;
			}

		}

		loopCount++;
	}

	/// calculate & store hit details if
	if (closestSphereIDX != -1) {

		glm::vec3 origin = ray.Origin - SphereList[closestSphereIDX].SphereOrigin;

		hitpoint = origin + ray.Direction * closestHit; // px = camera.x + direction.x * nt; py = camera.y + direction.y * nt; pz = camera.z + direction.z * nt;
		hitrecord.Hitpoint = hitpoint;
		hitrecord.Surfacenormal = glm::normalize(hitpoint);
		hitrecord.Hitpoint += SphereList[closestSphereIDX].SphereOrigin;
		hitrecord.Hitobjindex = closestSphereIDX;

		return true;
	}
	else {
		return false;
	}
}





























#if 0
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define logtime std::chrono::steady_clock::now()
#define elapsed std::chrono::duration_cast<std::chrono::milliseconds>
#define clock std::chrono::steady_clock
// 
//Catch the start time
clock::time_point start = logtime;
// 
//Catch the end time
clock::time_point end = clock::now();
printf("Last Frame Renderer => %d\n", elapsed(end - start).count());
//////////////////////////////////////////////////////////////////////////////////////////////////////

glm::vec4 Renderer::PerPixel(int x, int y) {

	Ray ray;
	ray.Origin = renderCam->GetPosition();
	ray.Direction = renderCam->GetRayDirection()[x + y * renderCam->GetViewPortWidth()] + Utils::Randomoffset1(-0.001f, 0.001f);

	Hitrec hitrecord;

	// Background color RGBa components
	glm::vec4 background = black;

	// Initialize the fragColor as black background
	glm::vec4 fragColor = background;

	float diffused;
	float ambient = 0.4f;
	glm::vec3 lightcolor{ 1.0f };
	float attenuation = 1.0f;

	for (int i = 0; i < renderScene->Bounces; i++) {
		if (Hittable(ray, renderScene->SphereList, hitrecord) == false) {

			glm::vec4 SkyColor = Utils::Lerp(ray, white, blue);

			fragColor += SkyColor * attenuation;

			return fragColor;
		}

		const Sphere& sphere = renderScene->SphereList[hitrecord.Hitobjindex];
		const Material& mat = renderScene->Materials[sphere.MatIndex];

		glm::vec3 Tolight(-renderScene->Lightdirection);
		diffused = glm::max(glm::dot(hitrecord.Surfacenormal, Tolight), 0.0f);

		glm::vec3 ambientcolor = mat.Albedo * ambient;
		glm::vec3 diffusedcolor = mat.Albedo * diffused * lightcolor;


		fragColor += glm::vec4(ambientcolor + diffusedcolor, 1.0f) * attenuation;

		attenuation *= 0.35f; // 0.5f

		ray.Origin = hitrecord.Hitpoint + hitrecord.Surfacenormal * 0.0001f;
		ray.Direction = glm::reflect(ray.Direction + mat.Roughness * Utils::Randomoffset2(-1.0f, 1.0f), hitrecord.Surfacenormal);
	}

	return fragColor;
}
#endif // 1