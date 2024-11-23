#include "HittableList.h"

HittableList::HittableList() : RootNode(nullptr) {}

HittableList::HittableList(std::shared_ptr<Hittable> object) : RootNode(nullptr) {
	Add(object);
}

void HittableList::Add(std::shared_ptr<Hittable> object) {
	ObjectList.emplace_back(object);

	bbox = Aabb(bbox, object->BoundingBox());
}

void HittableList::BuildBVH() {
	if (RootNode == nullptr) {
		if (ObjectList.size() == 0) return;

		RootNode = RootNode->SplitBvh(ObjectList, 0, ObjectList.size());
	}
}

bool HittableList::Hit(const Ray& ray, Interval raydist, Hitrec& hitrecord) const {
	/// Check if the ray hits any object within the list of objects
	return RootNode->Hit(ray, raydist, hitrecord);
}