#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class Triangle : public Hittable {
public:
	Triangle(const glm::dvec3& v0, const glm::dvec3& v1, const glm::dvec3& v2, std::shared_ptr<Material> matid);

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	bool isInterior(double u, double v, Hitrec& hitrecord) const;

private:
	glm::dvec3 V0{ 0.0 };
	glm::dvec3 V1{ 0.0 };
	glm::dvec3 V2{ 0.0 };
	glm::dvec3 W{ 0.0 };
	glm::dvec3 Normal;
	std::shared_ptr<Material> MaterialId;
	Aabb bbox;
	double D;
};