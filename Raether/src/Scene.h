#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"


class Sphere {
public:
	Sphere(glm::vec3 origin, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin),
																			  Radius(radius),
																			  MaterialId(matid),
																			  IsMoving(false)
	{ }

	Sphere(glm::vec3 origin1, glm::vec3 origin2, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin1),
																								  Radius(radius),
																								  MaterialId(matid),
																								  IsMoving(true)
	{
		SphereMotion = origin2 - origin1;
	}

	const glm::vec3 GetSphereOrigin(float time) const {
		// Linearly interpolate from center1 to center2 according to time,
		// Where time = 0 yields Origin1, and time = 1 yields Origin2
		return SphereOrigin + time * SphereMotion;
	}

public:
	glm::vec3 SphereOrigin{ 0.f };
	glm::vec3 SphereMotion{ 0.f };
	float Radius = 0.5f;
	std::shared_ptr<Material> MaterialId;
	bool IsMoving;
};

struct Scene {

	uint32_t SampleCount;
	uint32_t Bounces;

	std::vector<Sphere> SphereList;

	void setSampleCount(uint32_t count) {
		SampleCount = count;
	}
	void setSampleBounces(uint32_t bounces) {
		Bounces = bounces;
	}
	void addSpheres(Sphere sphere) {
		SphereList.emplace_back(sphere);
	}
};