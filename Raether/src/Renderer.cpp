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
}

bool Renderer::Inrange(float value, float low, float high) {
	if (value > low && value < high) {
		return true;
	}
	return false;
}

glm::vec4 Renderer::Lerp(const Ray& ray, glm::vec3 start, glm::vec3 end) {
	const float value = ray.Direction.y;
	
	float t = 0.5f + (value * 0.5f);

	/// Calculate linear color gradient using linear interpolation
	glm::vec4 lineargradient = glm::vec4((1 - t) * start + t * end, 1.0f);

	return lineargradient;
}

bool Renderer::Hittable(const Ray& ray, const std::vector<Sphere>& SphereList, Hitrec& hitrecord) {

	float closestHit = 101.0f; // hit out of range
	float T_min = 0.0f; // minimum hit distance
	float T_max = 100.0f; // maximum hit distance

	int loopCount = 0;

	const Sphere* closestSphere = nullptr;

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

		glm::vec3 neworigin = ray.Origin - sphere.sphereOrigin;

		float a = glm::dot(ray.Direction, ray.Direction); // (bx^2 + by^2 + bz^2)
		float b = 2.0f * (glm::dot(neworigin, ray.Direction)); // 2 ((ax * bx + ay * by + az * bz)
		float c = glm::dot(neworigin, neworigin) - sphere.radius * sphere.radius; // (ax^2 + ay^2 + az^2) - r^2

		float discriminant = (b * b) - (4.0f * a * c);

		/// Calculate if the ray hits the sphere or not
		if (discriminant >= 0.0f) {

			float HitDist = (-b - std::sqrt(discriminant)) / (2.0f * a); /// near hit distance

			if (loopCount == 0 && Inrange(HitDist, T_min, T_max)) {
				closestHit = HitDist;
				closestSphere = &sphere;
			}
			else if (HitDist < closestHit && Inrange(HitDist, T_min, T_max)) {
				closestHit = HitDist;
				closestSphere = &sphere;
			}

		}

		loopCount++;
	}

	/// calculate & store hit details if
	if (closestSphere != nullptr) {

		glm::vec3 origin = ray.Origin - closestSphere->sphereOrigin;

		hitpoint = origin + ray.Direction * closestHit; // px = camera.x + direction.x * nt; py = camera.y + direction.y * nt; pz = camera.z + direction.z * nt;

		hitrecord.Hitpoint = hitpoint;
		hitrecord.Surfacenormal = glm::normalize(hitpoint);
		hitrecord.HitColor = closestSphere->albedo;
		hitrecord.Hitobjorigin = closestSphere->sphereOrigin;

		return true;
	}
	else {
		return false; 
	}
}

glm::vec4 Renderer::CalculateColor(const Ray& ray, const Scene& scene, Hitrec& hitrecord) {

	// Background color RGBa components
	glm::vec4 background = black;

	// Initialize the fragColor as black background
	glm::vec4 fragColor = background;

	float luminance;

	if (Hittable(ray, scene.SphereList, hitrecord) == true) {

		glm::vec3 Tolight(-scene.Lightdirection);
		
		luminance = glm::max(glm::dot(hitrecord.Surfacenormal, Tolight), 0.0f);

		glm::vec3 normalview((hitrecord.Surfacenormal + 0.5f) * 0.5f);

		// calculate pixel color
		fragColor = glm::vec4(glm::vec3(hitrecord.HitColor * luminance), 1.0f); //normalview
		return fragColor;
	}
	else {
		fragColor = Lerp(ray, white, blue);
		// return skycolor
		return fragColor;
	}
}

void Renderer::Render(Raether& rae, const Scene& scene, const Camera& camera) {

	Ray ray;
	// Setting the Ray Origin
	ray.Origin = camera.GetPosition();

	int width = camera.GetViewPortWidth();
	int height = camera.GetViewPortHeight();

	Hitrec hitrecord;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			/// Setting the Ray Directions
			ray.Direction = camera.GetRayDirection()[x + y * width];

			/// Check Whether it hits something or not and return a color according to it
			glm::vec4 color = glm::clamp(CalculateColor(ray, scene, hitrecord), glm::vec4(0.0f), glm::vec4(1.0f));

			/// Draw the color using SDL
			rae.raeDrawCol(rae.raeCreateCol(Utils::converttoRGBA(color)));
			rae.raeDrawPix(x, height - y);
		}
	}
}