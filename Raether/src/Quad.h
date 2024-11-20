#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class Quad : public Hittable {
public:
	Quad(const glm::vec3& q, const glm::vec3& u, const glm::vec3& v, std::shared_ptr<Material> matid);

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

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

inline std::vector<std::shared_ptr<Hittable>> Box3D(const glm::vec3& a, const glm::vec3& b, std::shared_ptr<Material> matid) {
	
	/// Returns the 3D box (six sides) that contains the two opposite vertices a & b.
	std::vector<std::shared_ptr<Hittable>> quads;

	/// Construct the two opposite vertices with the minimum and maximum coordinates.
	glm::vec3 min = glm::vec3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
	glm::vec3 max = glm::vec3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

	glm::vec3 dx = glm::vec3((max.x - min.x), 0.0f, 0.0f);
	glm::vec3 dy = glm::vec3(0.0f, (max.y - min.y), 0.0f);
	glm::vec3 dz = glm::vec3(0.0f, 0.0f, (max.z - min.z));

	quads.emplace_back(std::make_shared<Quad>(glm::vec3(min.x, min.y, min.z), dz, dy, matid)); /// Left Quad
	quads.emplace_back(std::make_shared<Quad>(glm::vec3(max.x, min.y, min.z), dz, dy, matid)); /// Right Quad
	quads.emplace_back(std::make_shared<Quad>(glm::vec3(min.x, max.y, min.z), dx, dz, matid)); /// Top Quad
	quads.emplace_back(std::make_shared<Quad>(glm::vec3(min.x, min.y, min.z), dx, dz, matid)); /// Bottom Quad
	quads.emplace_back(std::make_shared<Quad>(glm::vec3(min.x, min.y, max.z), dx, dy, matid)); /// Back Quad
	quads.emplace_back(std::make_shared<Quad>(glm::vec3(min.x, min.y, min.z), dx, dy, matid)); /// Front Quad

	return quads;
}