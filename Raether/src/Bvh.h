#pragma once

#include <iostream>
#include <algorithm>

#include "Utils.h"
#include "Hittable.h"
#include "Aabb.h"

class BvhNode : public Hittable {
public:
	BvhNode() {}

	std::shared_ptr<BvhNode> SplitBvh(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end) {
		auto node = std::make_shared<BvhNode>();

		size_t listSpan = end - start;

		if (listSpan == 1) {
			node->LeftNode = node->RightNode = objects[start];
		}
		else if (listSpan == 2) {
			node->LeftNode = objects[start];
			node->RightNode = objects[start + 1];
		}
		else {

			#if RBVH==1

			// Split the BVH in Random Axis
			int randomAxis = Utils::RandomIntInRange(0, 2);
			auto comparator = (randomAxis == 0) ? BoxXCompare :
				(randomAxis == 1) ? BoxYCompare : BoxZCompare;
			
			#else
			
			Aabb box = objects[start]->BoundingBox();

			// Build the BVH
			for (size_t objectIdx = start + 1; objectIdx < end; objectIdx++) {
				box = Aabb(box, objects[objectIdx]->BoundingBox());
			}

			// Split the BVH in Longest Axis
			int longestAxis = box.LongestAxis();
			auto comparator = (longestAxis == 0) ? BoxXCompare :
				(longestAxis == 1) ? BoxYCompare : BoxZCompare;
			
			#endif

			std::sort(objects.begin() + start, objects.begin() + end, comparator);
			size_t mid = start + listSpan / 2;
			node->LeftNode = SplitBvh(objects, start, mid);
			node->RightNode = SplitBvh(objects, mid, end);
		}

		node->bbox = Aabb(node->LeftNode->BoundingBox(), node->RightNode->BoundingBox());
		return node;
	}

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override {
		// Create an Interval for the AABB hit check
		if (!bbox.Hit(ray, Interval(0.001f, hitrecord.ClosestHit))) {
			return false;
		}

		bool hit_left = LeftNode->Hit(ray, hitrecord);
		bool hit_right = RightNode->Hit(ray, hitrecord);

		return hit_left || hit_right;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	std::shared_ptr<Hittable> LeftNode;
	std::shared_ptr<Hittable> RightNode;
	Aabb bbox;

	static bool BoxCompare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b, int axis) {
		return a->BoundingBox().AxisInterval(axis).Min < b->BoundingBox().AxisInterval(axis).Min;
	}
	static bool BoxXCompare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
		return BoxCompare(a, b, 0);
	}
	static bool BoxYCompare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
		return BoxCompare(a, b, 1);
	}
	static bool BoxZCompare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
		return BoxCompare(a, b, 2);
	}
};