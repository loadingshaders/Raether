#pragma once

#include "Ray.h"

class Material;

class Hitrec {
public:
	glm::vec3 HitPoint;
	glm::vec3 SurfaceNormal;
	glm::vec3 HitColor;

	float ClosestHit;
	int CurrentObjId;
	int HitObjId;
	bool FrontFace;

	std::shared_ptr<Material> MatId;

	void SetFrontFace(const glm::vec3& rayDirection, glm::vec3& normal) {
		if (glm::dot(rayDirection, normal) > 0.f) {
			FrontFace = false;
		}
		else {
			FrontFace = true;
		}
		normal = FrontFace ? (normal) : (-normal);
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, Hitrec& hitrecord) const = 0;

public:
	glm::vec3 ObjectOrigin;
	std::shared_ptr<Material> ObjectMatId;
};