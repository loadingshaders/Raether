#pragma once

#include <iostream>

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
	glm::vec4 CalculateColor(const Ray& ray, const Scene& scene, Hitrec& hitrecord);
	bool Hittable(const Ray& ray, const std::vector<Sphere>& SphereList, Hitrec& hitrecord);

private:	
	glm::vec4 Lerp(const Ray& ray, glm::vec3 start, glm::vec3 end);
	bool Inrange(float value, float low, float high);
};