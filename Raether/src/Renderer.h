#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include "Raether.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#include "Utils.h"

#define black glm::vec3(0.0f, 0.0f, 0.0f)
#define white glm::vec3(1.0f)
#define blue glm::vec3(0.5294f, 0.8078f, 0.9215f) // glm::vec3(0.5f, 0.7f, 1.0f)

class Renderer {
public:
	Renderer();
	~Renderer();

	void Init(Raether& rae, const Scene& scene, Camera& camera);
	void Render(const Scene& scene, Camera& camera);
	void ResetFrameIdx() { FrameCount = 0; }

private:
	glm::vec3 PerPixel(glm::vec2 uv);
	bool Hittable(const Ray& ray, Hitrec& hitrecord);

public:
	Raether* raeObj;
	const Scene* renderScene;
	const Camera* renderCam;

private:
	uint32_t width;
	uint32_t height;
	uint32_t FrameCount;

	std::vector<glm::ui8_tvec4> ImageData;
	std::vector<glm::vec3> AccumImageData;
};