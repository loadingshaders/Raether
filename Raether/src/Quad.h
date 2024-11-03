#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class Quad : public Hittable {
public:
	Quad(const glm::vec3& q, const glm::vec3& u, const glm::vec3& v, std::shared_ptr<Material> matid);

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	bool isInterior(double a, double b, Hitrec& hitrecord) const;

private:
	glm::dvec3 Q{ 0.0 };
	glm::dvec3 U{ 0.0 };
	glm::dvec3 V{ 0.0 };
	glm::dvec3 W{ 0.0 };
	glm::dvec3 Normal;
	std::shared_ptr<Material> MaterialId;
	Aabb bbox;
	double D;
};

