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

	glm::vec3 Randomoffset(float from, float to) {
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
}
void Renderer::Render(Raether& rae, const Scene& scene, const Camera& camera) {

	renderCam = &camera;
	renderScene = &scene;

	int width = renderCam->GetViewPortWidth();
	int height = renderCam->GetViewPortHeight();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			/// Check Whether it hits something or not and return a color according to it
			glm::vec4 color = glm::clamp(PerPixel(x, y), glm::vec4(0.0f), glm::vec4(1.0f));

			/// Draw the color using SDL
			rae.raeDrawCol(rae.raeCreateCol(Utils::converttoRGBA(color)));
			rae.raeDrawPix(x, height - y);
		}
	}
}

glm::vec4 Renderer::PerPixel(int x, int y) {

	Ray ray;
	/// Setting the Ray Origin
	ray.Origin = renderCam->GetPosition();
	/// Setting the Ray Directions
	ray.Direction = renderCam->GetRayDirection()[x + y * renderCam->GetViewPortWidth()];

	Hitrec hitrecord;

	// Background color RGBa components
	glm::vec4 background = black;

	// Initialize the fragColor as black background
	glm::vec4 fragColor = background;

	float luminance;
	float multiplier = 1.0f;

	int bounce = 50;

	for (int i = 0; i < bounce; i++) {
		if (Hittable(ray, renderScene->SphereList, hitrecord) == false) {

			glm::vec4 SkyColor = Utils::Lerp(ray, white, blue);

			fragColor += SkyColor * multiplier;

			return fragColor;
		}

		const Sphere& sphere = renderScene->SphereList[hitrecord.Hitobjindex];
		const Material& mat = renderScene->Materials[sphere.MatIndex];

		glm::vec3 Tolight(-renderScene->Lightdirection);
		luminance = glm::max(glm::dot(hitrecord.Surfacenormal, Tolight), 0.0f);

		// glm::vec3 normalview((hitrecord.Surfacenormal + 0.5f) * 0.5f);
		// fragColor += glm::vec4(mat.Albedo * luminance, 1.0f) * multiplier;
		multiplier *= 0.5f;

		ray.Origin = hitrecord.Hitpoint + hitrecord.Surfacenormal * 0.0001f;
		ray.Direction = glm::reflect(ray.Direction, hitrecord.Surfacenormal + mat.Roughness * Utils::Randomoffset(-0.5f, 0.5f));
	}

	return fragColor;
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
		hitrecord.Hitpoint = hitrecord.Hitpoint + SphereList[closestSphereIDX].SphereOrigin;
		hitrecord.Hitobjindex = closestSphereIDX;

		return true;
	}
	else {
		return false;
	}
}