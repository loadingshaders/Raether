#include "Box.h"

Box::Box(const glm::vec3& a, const glm::vec3& b, std::shared_ptr<Material> matid) :
	MaterialId(matid)
{
	/// Construct the two opposite vertices with the minimum and maximum coordinates.
	Min = glm::vec3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
	Max = glm::vec3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

	/// Calculate Half Point for all Intervals
	this->ObjectOrigin = (Min + Max) * 0.5f;
	this->ObjectMatId = MaterialId;

	/// Calculate the Axis Interval
	glm::vec3 dx = glm::vec3(Max.x - Min.x, 0.0f, 0.0f);
	glm::vec3 dy = glm::vec3(0.0f, Max.y - Min.y, 0.0f);
	glm::vec3 dz = glm::vec3(0.0f, 0.0f, Max.z - Min.z);

	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Min.x, Min.y, Min.z), dz, dy, matid)); /// Left Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Max.x, Min.y, Min.z), dz, dy, matid)); /// Right Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Min.x, Max.y, Min.z), dx, dz, matid)); /// Top Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Min.x, Min.y, Min.z), dx, dz, matid)); /// Bottom Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Min.x, Min.y, Max.z), dx, dy, matid)); /// Back Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::vec3(Min.x, Min.y, Min.z), dx, dy, matid)); /// Front Quad

	/// Consider two of the points min and max and construct a box with those two points
	bbox = Aabb(Min, Max);

	/// Calculate the rootnode for all quads of the Box
	RootNode = RootNode->SplitBvh(Quads, 0, Quads.size());
}

bool Box::Hit(const Ray& ray, Hitrec& hitrecord) const {
	return RootNode->Hit(ray, hitrecord);
}