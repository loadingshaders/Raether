#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"


class Sphere : public Hittable {
public:
	Sphere(glm::vec3 origin, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin),
																			  Radius(radius),
																			  MaterialId(matid),
																			  IsMoving(false)
	{ }

	Sphere(glm::vec3 origin1, glm::vec3 origin2, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin1),
																								  Radius(radius),
																								  MaterialId(matid),
																								  IsMoving(true)
	{
		SphereMotion = origin2 - origin1;
	}

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override {
		/// Check for sphere hit and update hitrecord

		/// Sphere Equation
		/// (bx^2 + by^2 + bz^2)t^2 + 2 ( (ax*bx + ay*by + az*bz) + (ax^2 + ay^2 + az^2) - r^2 = 0
		// a = camera/ray origin (ax, ay, az)
		// b = ray direction (bx, by, bz)
		// t = hit distance
		// A , B , C = sphere origin
		// r = sphere radius

		glm::vec3 sphereOrigin = (IsMoving) ? GetSphereOrigin(ray.GetTime()) : SphereOrigin;
		glm::vec3 newrayOrigin = ray.Origin - sphereOrigin;

		float a = glm::dot(ray.Direction, ray.Direction); // (bx^2 + by^2 + bz^2)
		float b = 2.f * (glm::dot(newrayOrigin, ray.Direction)); // 2 ((ax * bx + ay * by + az * bz)
		float c = glm::dot(newrayOrigin, newrayOrigin) - Radius * Radius; // (ax^2 + ay^2 + az^2) - r^2

		float discriminant = (b * b) - (4.f * a * c);

		/// Calculate if the ray hits the sphere or not
		if (discriminant >= 0.0f) {
			float nearHit = (-b - std::sqrt(discriminant)) / (2.f * a);

			// Check if this is the closest hit
			if (nearHit < hitrecord.ClosestHit && Utils::Inrange(nearHit, nearDist, farDist)) {

				glm::vec3 hitPoint = ray.Origin + nearHit * ray.Direction;
				hitrecord.HitPoint = hitPoint;
				hitrecord.SurfaceNormal = glm::normalize(hitPoint - sphereOrigin);
				hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
				hitrecord.MatId = MaterialId;
				hitrecord.ClosestHit = nearHit;
				hitrecord.HitObjId = hitrecord.CurrentObjId;

				return true;
			}
		}

		return false;
	}

	const glm::vec3 GetSphereOrigin(float time) const {
		// Linearly interpolate from center1 to center2 according to time,
		// Where time = 0 yields Origin1, and time = 1 yields Origin2
		return SphereOrigin + time * SphereMotion;
	}

public:
	glm::vec3 SphereOrigin{ 0.f };
	glm::vec3 SphereMotion{ 0.f };
	float Radius = 0.5f;
	std::shared_ptr<Material> MaterialId;
	bool IsMoving;
};

class Scene : public Hittable {
public:
	Scene() {}

	void SetSampleCount(uint32_t count) { SampleCount = count; }
	void SetSampleBounces(uint32_t bounces) { Bounces = bounces; }

	const uint32_t GetSampleCount() const { return SampleCount; }
	const uint32_t GetSampleBounces() const { return Bounces; }

	void Add(std::shared_ptr<Hittable> objects) {
		ObjectList.emplace_back(objects);
	}

	bool Hit(const Ray& ray, Hitrec& hitrecord) const override {
		/// Check if the ray hits anything in the scene

		/// Initialize hitrcord
		hitrecord.ClosestHit = std::numeric_limits<float>::max();
		hitrecord.HitObjId = -1;

		for (int loopcount = 0; loopcount < ObjectList.size(); loopcount++) {

			/// Pass the current object id
			hitrecord.CurrentObjId = loopcount;

			/// Check the hit
			ObjectList[loopcount]->Hit(ray, hitrecord);
		}

		return hitrecord.HitObjId != -1;
	}

private:
	uint32_t SampleCount;
	uint32_t Bounces;

	std::vector<std::shared_ptr<Hittable>> ObjectList;
};