#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable {
public:
	Sphere(glm::dvec3 origin, double radius, std::shared_ptr<Material> matid);
	Sphere(glm::dvec3 origin1, glm::dvec3 origin2, double radius, std::shared_ptr<Material> matid);

	const glm::dvec3 GetSphereOrigin(double time) const;
	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	static void GetSphereUV(const glm::dvec3& point, double& u, double& v);

private:
	glm::dvec3 SphereOrigin{ 0.0 };
	glm::dvec3 SphereMotion{ 0.0 };
	double Radius = 0.5;
	std::shared_ptr<Material> MaterialId;
	bool IsMoving;
	Aabb bbox;
};