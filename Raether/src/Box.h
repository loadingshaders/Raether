#pragma once

#include "Quad.h"
#include "Bvh.h"

class Box : public Hittable {
public:
	Box(const glm::vec3& a, const glm::vec3& b, std::shared_ptr<Material> matid);
	Box(const glm::vec3& origin, std::shared_ptr<Material> matid, const glm::vec3& boxwidth);

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	glm::vec3 Min;
	glm::vec3 Max;
	std::shared_ptr<Material> MaterialId;
	Aabb bbox;
	std::vector<std::shared_ptr<Hittable>> Quads;
	std::shared_ptr<BvhNode> RootNode;
};

