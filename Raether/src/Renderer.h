#pragma once

#include <iostream>
#include <random>

#include "Raether.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

#define black glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
#define white glm::vec3(1.0f)
#define blue glm::vec3(0.5f, 0.7f, 1.0f)

class Renderer {
public:
	Renderer();
	~Renderer();

	void Render(Raether& rae, const Scene& scene, const Camera& camera);
private:
	const Camera* renderCam = nullptr;
	const Scene* renderScene = nullptr;
private:
	glm::vec4 PerPixel(int x, int y);
	bool Hittable(const Ray& ray, const std::vector<Sphere>& SphereList, Hitrec& hitrecord);
private:	
	glm::vec4 Lerp(const Ray& ray, glm::vec3 start, glm::vec3 end);
	bool Inrange(float value, float low, float high);
};