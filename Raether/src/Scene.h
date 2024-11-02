#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"
#include "Bvh.h"

class Sphere : public Hittable {
public:
	Sphere(glm::vec3 origin, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin),
																			  Radius(radius),
																			  MaterialId(matid),
																			  IsMoving(false)
	{
		this->ObjectOrigin = SphereOrigin;
		this->ObjectMatId = MaterialId;

		/// Initialize the Bounding Volume for Stationary Sphere
		glm::vec3 rvec = glm::vec3(Radius, Radius, Radius);
		bbox = Aabb(origin - rvec, origin + rvec);
	}

	Sphere(glm::vec3 origin1, glm::vec3 origin2, float radius, std::shared_ptr<Material> matid) : SphereOrigin(origin1),
																								  Radius(radius),
																								  MaterialId(matid),
																								  IsMoving(true)
	{
		this->ObjectOrigin = SphereOrigin;
		this->ObjectMatId = MaterialId;

		SphereMotion = origin2 - origin1;

		/// Initialize the Bounding Volume for Non-Stationary Sphere
		glm::vec3 rvec = glm::vec3(Radius, Radius, Radius);
		Aabb bbox1 = Aabb(origin1 - rvec, origin1 + rvec);
		Aabb bbox2 = Aabb(origin2 - rvec, origin2 + rvec);
		bbox = Aabb(bbox1, bbox2);
	}

	const glm::vec3 GetSphereOrigin(float time) const {
		// Linearly interpolate from center1 to center2 according to time,
		// Where time = 0 yields Origin1, and time = 1 yields Origin2
		return SphereOrigin + time * SphereMotion;
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

		glm::dvec3 sphereOrigin = (IsMoving) ? glm::dvec3(GetSphereOrigin(ray.GetTime())) : glm::dvec3(SphereOrigin);
		glm::dvec3 newrayOrigin = glm::dvec3(ray.Origin) - sphereOrigin;

		double a = glm::dot(glm::dvec3(ray.Direction), glm::dvec3(ray.Direction)); // (bx^2 + by^2 + bz^2)
		double b = 2.0 * (glm::dot(newrayOrigin, glm::dvec3(ray.Direction))); // 2 ((ax * bx + ay * by + az * bz)
		double c = glm::dot(newrayOrigin, newrayOrigin) - Radius * Radius; // (ax^2 + ay^2 + az^2) - r^2

		/// Case-1: Calculate if the ray hits the sphere or not
		double discriminant = (b * b) - (4.0 * a * c);
		if (discriminant < 0.0f) return false;

		/// Case-2: Check if this is the closest hit
		double nearHit = (-b - std::sqrt(discriminant)) / (2.0 * a);
		if (!(nearHit < hitrecord.ClosestHit) || !Utils::Inrange(nearHit, nearDist, farDist)) return false;

		glm::vec3 hitPoint = ray.Origin + (float)nearHit * ray.Direction;
		hitrecord.HitPoint = hitPoint;
		hitrecord.SurfaceNormal = glm::normalize(hitPoint - glm::vec3(sphereOrigin));
		hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
		GetSphereUV(hitrecord.SurfaceNormal, hitrecord.U, hitrecord.V);
		hitrecord.MatId = MaterialId;
		hitrecord.ClosestHit = nearHit;

		return true;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	glm::vec3 SphereOrigin{ 0.f };
	glm::vec3 SphereMotion{ 0.f };
	float Radius = 0.5f;
	std::shared_ptr<Material> MaterialId;
	bool IsMoving;
	Aabb bbox;

	static void GetSphereUV(const glm::vec3& point, double& u, double& v) {
		// Calculate phi and theta
		// phi -> denotes longitude or how far around the point is on equator
		// theta -> denotes latitude or how far up or down

		// The atan2(y, x) function gives you the angle between the positive x - axis and the point(x, y) on a 2D plane.
		/// In this case, we’re looking at the x and z coordinates because we want to know the angle around the Y - axis.
		/// By adding PI(180 degrees), we ensure that PHI will always be in the range[0, 2*PI](a full circle).
		/// Which matches what we need for u(the texture's horizontal position).
		double phi = std::atan2(-point.z, point.x) + PI;

		// The y - coordinate of the point tells you how far "up" the point is on the sphere.
		/// The arccos(acos) function gives the angle whose cosine is the given value. Since the y - coordinate tells the vertical position,
		/// we use it to calculate how far up or down the point is.
		/// We use - y because THETA measures from the bottom of the sphere(the South Pole), and the y - coordinate gets smaller as you move down
		/// from the top.
		double theta = std::acos(-point.y);

		u = phi / (2.0 * PI);
		v = theta / PI;
	}
};

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