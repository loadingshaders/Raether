#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"
#include "Bvh.h"
#include "Sphere.h"

class Scene : public Hittable {
public:
	Scene() {}

	void SetSampleCount(uint32_t count) { SampleCount = count; }
	void SetSampleBounces(uint32_t bounces) { Bounces = bounces; }

	const uint32_t GetSampleCount() const { return SampleCount; }
	const uint32_t GetSampleBounces() const { return Bounces; }
	const std::vector<std::shared_ptr<Hittable>>& GetObjectList() const { return ObjectList; }

	void Add(std::shared_ptr<Hittable> objects) {

		ObjectList.emplace_back(objects);

		bbox = Aabb(bbox, objects->BoundingBox());
	}

	void BuildBVH() {
		RootNode = RootNode->SplitBvh(ObjectList, 0, ObjectList.size());
	}

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override {
		/// Check if the ray hits anything in the scene

		/// Initialize hitrcord
		hitrecord.ClosestHit = std::numeric_limits<float>::max();

		return RootNode->Hit(ray, hitrecord);
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	uint32_t SampleCount;
	uint32_t Bounces;
	std::vector<std::shared_ptr<Hittable>> ObjectList;
	Aabb bbox;
	std::shared_ptr<BvhNode> RootNode;
};