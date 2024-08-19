#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#define near 0.001f
#define far 10000.f

struct Material {
	glm::vec3 Albedo{ 1.0f };
	glm::vec3 EmissionColor{ 0.0f };
	float EmissionStrength{ 0.0f };
	float Roughness{ 0.1f };
	float Metallic{ 0.0 };
};

struct Sphere {
	glm::vec3 SphereOrigin{ 0.0f };
	float Radius = 0.5f;

	int MatIndex = 0;
};

struct Scene {

	uint32_t SampleCount;
	uint32_t Bounces;

	std::vector<Sphere> SphereList;
	std::vector<Material> Materials;

	void setSampleCount(uint32_t count) {
		SampleCount = count;
	}
	void setSampleBounces(uint32_t bounces) {
		Bounces = bounces;
	}
	void addSpheres(Sphere sphere) {
		SphereList.push_back(sphere);
	}
	void addMaterials(Material mat) {
		Materials.push_back(mat);
	}
};

struct Hitrec {
	glm::vec3 HitPoint;
	glm::vec3 SurfaceNormal;
	glm::vec3 HitColor;
	int HitObjId;
};

