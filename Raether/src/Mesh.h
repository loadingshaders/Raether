#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "glm\glm.hpp"

#include "json\json.hpp"
#include "stb\stb_image.h"
#include "stb\stb_image_write.h"
#include "tinygltf\tiny_gltf.h"

#include "Material.h"
#include "Hittable.h"
#include "Aabb.h"
#include "Bvh.h"
#include "Triangle.h"

class Mesh : public Hittable {
public:
	Mesh(const char* modelFilename, double scale, std::shared_ptr<Material> matid);

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return bbox; }

private:
	void Add(std::shared_ptr<Hittable> object);

	void BuildBVH();

	bool LoadModel(std::string& modelFilename, std::string& err, std::string& warn);

private:
	double Scale;
	std::shared_ptr<Material> MaterialId;
	Aabb bbox;
	std::vector<std::shared_ptr<Hittable>> TriangleMesh;
	std::shared_ptr<BvhNode> RootNode;
};