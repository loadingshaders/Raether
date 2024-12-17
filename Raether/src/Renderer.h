#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <execution>

#include "Raether.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#include "Utils.h"
#include "Config.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void Init(Raether& rae, const Scene& scene, Camera& camera);
	void Render(const Scene& scene, Camera& camera);
	void ResetFrameIdx() { FrameCount = 0; }

private:
	glm::dvec3 PerPixel(glm::dvec2 uv);
	void SetBuffers();

public:
	Raether* raeObj;
	const Scene* renderScene;
	const Camera* renderCam;

private:
	uint32_t width;
	uint32_t height;
	uint32_t FrameCount;

	std::vector<GLM::ui8_tvec4> ImageData;
	std::vector<glm::dvec3> AccumImageData;

	std::vector<uint32_t> ImageHorizontalIter, ImageVerticalIter;
};