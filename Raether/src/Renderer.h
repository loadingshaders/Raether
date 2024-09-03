#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include "Raether.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#include "Utils.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void Init(Raether& rae, const Scene& scene, Camera& camera);
	void Render(const Scene& scene, Camera& camera);
	void ResetFrameIdx() { FrameCount = 0; }

private:
	glm::vec3 PerPixel(glm::vec2 uv);

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