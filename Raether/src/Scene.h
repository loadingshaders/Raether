#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

struct Material {
	glm::vec3 Albedo{ 1.0f };
	float Roughness{ 0.1f };
	float Metallic{ 0.0 };
};

struct Sphere {
	glm::vec3 SphereOrigin{ 0.0f };
	float Radius = 0.5f;

	int MatIndex = 0;
};

struct Scene {

	float SampleCount;

	glm::vec3 Lightdirection;

	std::vector<Sphere> SphereList;
	std::vector<Material> Materials;

	void addSpheres(Sphere sphere) {
		SphereList.push_back(sphere);
	}
	void addMaterials(Material mat) {
		Materials.push_back(mat);
	}
};

struct Hitrec {
	glm::vec3 Hitpoint;
	glm::vec3 Surfacenormal;
	glm::vec3 HitColor;
	int Hitobjindex;
};

