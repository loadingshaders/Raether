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

	SetBuffers();
}

void Renderer::SetBuffers() {
	width = renderCam->GetViewPortWidth();
	height = renderCam->GetViewPortHeight();

	ImageHorizontalIter.resize(width);
	ImageVerticalIter.resize(height);

	for (uint32_t i = 0; i < width; i++) {
		ImageHorizontalIter[i] = i;
	}
	for (uint32_t j = 0; j < height; j++) {
		ImageHorizontalIter[j] = j;
	}

	ImageData.resize((uint64_t)(width * height));
	AccumImageData.resize((uint64_t)(width * height));
}

void Renderer::Render(const Scene& scene, Camera& camera) {

	if (FrameCount == 0) {
		/// Reset the Accumulate ImgaeBuffer
		memset(&AccumImageData[0], 0, width * height * sizeof(glm::vec3));
	}

	else if (FrameCount < renderScene->GetSampleCount()) {
		
		#define MT 0
		#if MT == 1
		std::for_each(std::execution::par, ImageHorizontalIter.begin(), ImageHorizontalIter.end(),
			[this](uint32_t y){
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
			});

		#else
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
		#endif

		/// Draw the color using SDL
		raeObj->raeDrawImage(ImageData);
	}
	if (FrameCount <= renderScene->GetSampleCount()) {
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

	for (uint32_t bounces = 0; bounces < renderScene->GetSampleBounces(); bounces++) {

		if (renderScene->Hit(ray, hitrecord)) {

			const std::shared_ptr<Material>& mat = hitrecord.MatId;
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