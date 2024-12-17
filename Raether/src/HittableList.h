#pragma once

#include <iostream>

#include "Hittable.h"
#include "Aabb.h"
#include "Bvh.h"

class HittableList : public Hittable {
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	void Add(std::shared_ptr<Hittable> object);

	void BuildBVH();

	bool Hit(const Ray& ray, Interval raydist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	std::vector<std::shared_ptr<Hittable>> ObjectList;
	Aabb bbox;
	std::shared_ptr<BvhNode> RootNode;
};