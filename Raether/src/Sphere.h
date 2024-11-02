#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable {
public:
	Sphere(glm::vec3 origin, float radius, std::shared_ptr<Material> matid);
	Sphere(glm::vec3 origin1, glm::vec3 origin2, float radius, std::shared_ptr<Material> matid);

	const glm::vec3 GetSphereOrigin(float time) const;
	bool Hit(const Ray& ray, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	static void GetSphereUV(const glm::vec3& point, double& u, double& v);

private:
	glm::vec3 SphereOrigin{ 0.f };
	glm::vec3 SphereMotion{ 0.f };
	float Radius = 0.5f;
	std::shared_ptr<Material> MaterialId;
	bool IsMoving;
	Aabb bbox;
};

