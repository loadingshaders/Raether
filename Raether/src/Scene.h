#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"
#include "Bvh.h"

class Scene : public Hittable {
public:
	Scene() {}
	Scene(std::shared_ptr<Hittable> object) { Add(object); }

	void SetSampleCount(uint32_t count) { SampleCount = count; }
	void SetSampleBounces(uint32_t bounces) { Bounces = bounces; }
	void SetBackgroundColor(const glm::dvec3 topcolor, const glm::dvec3 bottomcolor) {
		BackgroundColorNorth = topcolor;
		BackgroundColorSouth = bottomcolor;
	}

	const glm::dvec3 GetBackgroundColorNorth() const { return  BackgroundColorNorth; }
	const glm::dvec3 GetBackgroundColorSouth() const { return  BackgroundColorSouth; }
	const uint32_t GetSampleCount() const { return SampleCount; }
	const uint32_t GetSampleBounces() const { return Bounces; }
	const std::vector<std::shared_ptr<Hittable>>& GetObjectList() const { return ObjectList; }

	void Add(std::shared_ptr<Hittable> object) {
		ObjectList.emplace_back(object);

		bbox = Aabb(bbox, object->BoundingBox());
	}

	void Add(std::vector<std::shared_ptr<Hittable>> objects) {
		for (auto object : objects) {
			Add(object);
		}
	}

	void Clear() {
		ObjectList.clear();
	}

	void BuildBVH() {
		RootNode = RootNode->SplitBvh(ObjectList, 0, ObjectList.size());
	}

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override {
		/// Check if the ray hits anything in the scene
		return RootNode->Hit(ray, hitdist, hitrecord);
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	uint32_t SampleCount;
	uint32_t Bounces;
	std::vector<std::shared_ptr<Hittable>> ObjectList;
	Aabb bbox;
	std::shared_ptr<BvhNode> RootNode;
	glm::dvec3 BackgroundColorNorth;
	glm::dvec3 BackgroundColorSouth;
};