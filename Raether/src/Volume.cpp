#include "Volume.h"

Volume::Volume(std::shared_ptr<Hittable> boundary, float density, glm::vec3& albedo) :
	Boundary(boundary),
	NegInvDensity(-(1.0f / density)),
	PhaseFunction(std::make_shared<Isotropic>(albedo))
{}

Volume::Volume(std::shared_ptr<Hittable> boundary, float density, std::shared_ptr<Texture> texture) :
	Boundary(boundary),
	NegInvDensity(-(1.0f / density)),
	PhaseFunction(std::make_shared<Isotropic>(texture))
{}

bool Volume::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
	Hitrec rec1, rec2;

	/// Case-1: Check if entry point exists and store hit distance
	if (!Boundary->Hit(ray, Interval::Universe, rec1)) return false;

	/// Case-2: Check if the exit point exists using offset ray
	if (!Boundary->Hit(ray, Interval(rec1.ClosestHit + 0.0001, Infinity), rec2)) return false;

	/// Case-3: Check if hit points are in correct order and range
	if (rec1.ClosestHit < hitdist.Min) rec1.ClosestHit = hitdist.Min;
	if (rec2.ClosestHit > hitdist.Max) rec2.ClosestHit = hitdist.Max;

	if (rec1.ClosestHit >= rec2.ClosestHit) return false;

	if (rec1.ClosestHit < 0.0) rec1.ClosestHit = 0.0;

	// Calculate random hit point using exponential distribution
	double rayLength = glm::length(ray.Direction);
	double distanceInside = (rec2.ClosestHit - rec1.ClosestHit) * rayLength;
	double hitDistance = NegInvDensity * std::log(Utils::RandomDouble());

	/// Case-4: Check if the random hit point is within the volume
	if (hitDistance > distanceInside) return false;

	/// Case-5: Perfrom subsurface scatter and update hit record
	hitrecord.ClosestHit = rec1.ClosestHit + hitDistance / rayLength;
	hitrecord.HitPoint = ray.Origin + (float)hitrecord.ClosestHit * ray.Direction;
	hitrecord.SurfaceNormal = glm::vec3(1.0f, 0.0f, 0.0f);
	hitrecord.FrontFace = true;
	hitrecord.MatId = PhaseFunction;

	return true;
}