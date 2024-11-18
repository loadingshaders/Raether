#pragma once

#include <iostream>

#include "Hittable.h"
#include "Material.h"

class Volume : public Hittable {
public:
	Volume(std::shared_ptr<Hittable> boundary, float density, glm::vec3& albedo);
	Volume(std::shared_ptr<Hittable> boundary, float density, std::shared_ptr<Texture> texture);

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override;

	Aabb BoundingBox() const override { return Boundary->BoundingBox(); }

private:
	std::shared_ptr<Hittable> Boundary;
	float NegInvDensity;
	std::shared_ptr<Material> PhaseFunction;
};

