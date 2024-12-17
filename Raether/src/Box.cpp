#include "Box.h"

Box::Box(const glm::dvec3& a, const glm::dvec3& b, std::shared_ptr<Material> matid) :
	MaterialId(matid)
{
	/// Construct the two opposite vertices with the minimum and maximum coordinates.
	Min = glm::dvec3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
	Max = glm::dvec3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

	/// Calculate Half Point for all Intervals
	this->ObjectOrigin = (Min + Max) * 0.5;
	this->ObjectMatId = MaterialId;

	/// Calculate the Axis Interval
	glm::dvec3 dx = glm::dvec3((Max.x - Min.x), 0.0, 0.0);
	glm::dvec3 dy = glm::dvec3(0.0, (Max.y - Min.y), 0.0);
	glm::dvec3 dz = glm::dvec3(0.0, 0.0, (Max.z - Min.z));

	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Min.x, Min.y, Min.z), dz, dy, matid)); /// Left Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Max.x, Min.y, Min.z), dz, dy, matid)); /// Right Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Min.x, Max.y, Min.z), dx, dz, matid)); /// Top Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Min.x, Min.y, Min.z), dx, dz, matid)); /// Bottom Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Min.x, Min.y, Max.z), dx, dy, matid)); /// Back Quad
	Quads.emplace_back(std::make_shared<Quad>(glm::dvec3(Min.x, Min.y, Min.z), dx, dy, matid)); /// Front Quad

	/// Consider two of the points min and max and construct a box with those two points
	bbox = Aabb(Min, Max);

	/// Calculate the rootnode for all quads of the Box
	RootNode = RootNode->SplitBvh(Quads, 0, Quads.size());
}

Box::Box(const glm::dvec3& origin, std::shared_ptr<Material> matid, const glm::dvec3& boxwidth) :
	Box(origin - (boxwidth * 0.5),
		origin + (boxwidth * 0.5),
		matid)
{
}

bool Box::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
	/// Check if the ray hits any quad within the sides
	return RootNode->Hit(ray, hitdist, hitrecord);
}