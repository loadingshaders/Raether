#pragma once

#include "Quad.h"
#include "Bvh.h"

class Box : public Hittable {
public:
	Box(const glm::dvec3& a, const glm::dvec3& b, std::shared_ptr<Material> matid);
	Box(const glm::dvec3& origin, std::shared_ptr<Material> matid, const glm::dvec3& boxwidth);

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	glm::dvec3 Min;
	glm::dvec3 Max;
	std::shared_ptr<Material> MaterialId;
	Aabb bbox;
	std::vector<std::shared_ptr<Hittable>> Quads;
	std::shared_ptr<BvhNode> RootNode;
};