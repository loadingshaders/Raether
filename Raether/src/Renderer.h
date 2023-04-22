#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include "Raether.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

#define black glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
#define white glm::vec3(1.0f)
#define blue glm::vec3(0.5f, 0.7f, 1.0f)

#define logtime std::chrono::steady_clock::now()
#define elapsed std::chrono::duration_cast<std::chrono::milliseconds>


class Renderer {
public:
	Renderer();
	~Renderer();

	void Init(Raether& rae, const Scene& scene, Camera& camera);

	void Render(const Scene& scene, Camera& camera);

	void ResetFrameIdx() { FrameCount = 1; }

	const Camera* renderCam = nullptr;
	const Scene* renderScene = nullptr;
	Raether* raeObj = nullptr;
private:
	int FrameCount = 1;

	std::vector<glm::ui8_tvec4> PixelData;
	std::vector<glm::vec4> AccumPixelData;
private:
	glm::vec4 PerPixel(int x, int y);
	bool Hittable(const Ray& ray, const std::vector<Sphere>& SphereList, Hitrec& hitrecord);
private:
	glm::ui8_tvec4 GammaCorrection(glm::vec4 color);
};