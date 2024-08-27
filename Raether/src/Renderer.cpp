#include "Renderer.h"

Renderer::Renderer() : width(800),
					   height(800),
					   raeObj(nullptr),
					   renderScene(nullptr),
					   renderCam(nullptr),
					   FrameCount(1)
{
}
Renderer::~Renderer() { }

void Renderer::Init(Raether& rae, const Scene& scene, Camera& camera) {
	raeObj = &rae;
	renderCam = &camera;
	renderScene = &scene;
}

void Renderer::Render(const Scene& scene, Camera& camera) {

	width = renderCam->GetViewPortWidth();
	height = renderCam->GetViewPortHeight();

	ImageData.resize((uint64_t)(width * height));
	AccumImageData.resize((uint64_t)(width * height));

	if (FrameCount == 0) {
		/// Reset the Accumulate ImgaeBuffer
		memset(&AccumImageData[0], 0, width * height * sizeof(glm::vec3));
	}

	else if (FrameCount < renderScene->SampleCount) {

		for (uint32_t y = 0; y < height; y++) {
			for (uint32_t x = 0; x < width; x++) {

				/// Accumulate the color
				AccumImageData[x + y * width] += PerPixel(glm::vec2(x, (height - 1) - y));

				glm::vec3 accumColor = AccumImageData[(uint64_t)(x + y * width)];

				/// Adjust the brightness
				accumColor /= (float)FrameCount;

				accumColor = glm::clamp(accumColor, glm::vec3(0.0f), glm::vec3(1.0f));

				/// Store the color data
				ImageData[(uint64_t)(x + y * width)] = Utils::converttoRGBA(glm::vec4(accumColor, 1.f));
			}
		}
		/// Draw the color using SDL
		raeObj->raeDrawImage(ImageData);
	}
	if (FrameCount <= renderScene->SampleCount) {
		FrameCount++;
	}
}

glm::vec3 Renderer::PerPixel(glm::vec2 uv) {

	Ray ray;
	ray.Direction = renderCam->GetRayDirection()[(uint64_t)(uv.x + uv.y * renderCam->GetViewPortWidth())];
	ray.Time = renderCam->GetRayTime();

	if (renderCam->GetDefocusStrength() <= 0.f) {
		ray.Origin = renderCam->GetPosition();
	}
	else {
		glm::vec3 focusPoint = renderCam->GetPosition() + ray.Direction * renderCam->GetFocusDistance();
		ray.Origin = renderCam->GetDefocusDiskSample();
		ray.Direction = glm::normalize(focusPoint - ray.Origin);
	}

	ray.Direction += Utils::RandomOffset(-0.002f, 0.002f) * renderCam->GetCamFovFraction();

	Hitrec hitrecord;

	glm::vec3 hitColor = glm::vec3(1.f);

	for (uint32_t bounces = 0; bounces < renderScene->Bounces; bounces++) {

		if (Hittable(ray, hitrecord) == true) {

			const Sphere& sphere = renderScene->SphereList[hitrecord.HitObjId];
			const std::shared_ptr<Material> mat = sphere.MaterialId;

			glm::vec3 attenuation;

			if (mat->Scatter(ray, hitrecord, attenuation)) {
				hitColor *= attenuation;
			}

			ray.Direction += Utils::RandomOffset(-0.001f, 0.001f) * renderCam->GetCamFovFraction();
		}
		else {
			hitColor *= Utils::Lerp(ray.Direction, blue, white);
			break;
		}
	}

	return hitColor;
}

bool Renderer::Hittable(const Ray& ray, Hitrec& hitrecord) {

	float closestHit = 101.0f; // hit out of range
	int closestSphereIDX = -1;

	glm::vec3 hitpoint = glm::vec3(0.0f);
	glm::vec3 origin = glm::vec3(0.0f);

	/// Check the hit
	for (int loopCount = 0; loopCount < renderScene->SphereList.size(); loopCount++) {

		const Sphere& sphere = renderScene->SphereList[loopCount];

		/// Sphere Equation
		/// (bx^2 + by^2 + bz^2)t^2 + 2 ( (ax*bx + ay*by + az*bz) + (ax^2 + ay^2 + az^2) - r^2 = 0
		// a = camera/ray origin (ax, ay, az)
		// b = ray direction (bx, by, bz)
		// t = hit distance
		// A , B , C = sphere origin
		// r = sphere radius

		glm::vec3 sphereOrigin = (sphere.IsMoving) ? sphere.GetSphereOrigin(ray.GetTime()) : sphere.SphereOrigin;
		glm::vec3 newrayOrigin = ray.Origin - sphereOrigin;

		float a = glm::dot(ray.Direction, ray.Direction); // (bx^2 + by^2 + bz^2)
		float b = 2.f * (glm::dot(newrayOrigin, ray.Direction)); // 2 ((ax * bx + ay * by + az * bz)
		float c = glm::dot(newrayOrigin, newrayOrigin) - sphere.Radius * sphere.Radius; // (ax^2 + ay^2 + az^2) - r^2

		float discriminant = (b * b) - (4.f * a * c);

		/// Calculate if the ray hits the sphere or not
		if (discriminant >= 0.0f) {

			float nearHit = (-b - std::sqrt(discriminant)) / (2.f * a);

			if (nearHit < closestHit && Utils::Inrange(nearHit, nearDist, farDist)) {
				closestHit = nearHit;
				closestSphereIDX = loopCount;
			}
		}
	}

	/// Calculate & store hit details
	if (closestSphereIDX != -1) {

		glm::vec3 origin = ray.Origin - renderScene->SphereList[closestSphereIDX].SphereOrigin;
		hitpoint = origin + ray.Direction * closestHit; // px = camera.x + direction.x * nt; py = camera.y + direction.y * nt; pz = camera.z + direction.z * nt;
		hitrecord.HitPoint = hitpoint;
		hitrecord.SurfaceNormal = glm::normalize(hitpoint);
		hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
		hitrecord.HitPoint += renderScene->SphereList[closestSphereIDX].SphereOrigin;
		hitrecord.HitObjId = closestSphereIDX;

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
#endif