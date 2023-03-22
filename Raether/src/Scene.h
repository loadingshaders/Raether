#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

struct Materials {

};

struct Sphere {
	glm::vec3 sphereOrigin{ 0.0f };
	float radius = 0.5f;
	glm::vec3 albedo{ 1.0f };
};

struct Scene {
	glm::vec3 Lightdirection;

	std::vector<Sphere> SphereList;

	void addSpheres(Sphere sphere) {
		SphereList.push_back(sphere);
	}
};

struct Hitrec {
	glm::vec3 Hitpoint;
	glm::vec3 Surfacenormal;
	glm::vec3 HitColor;
	glm::vec3 Hitobjorigin;
};

