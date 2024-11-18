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

bool Volume::Hit(const Ray& ray, Hitrec& hitrecord) const {
	double hitDist1, hitDist2;
	double originalClosestHit = hitrecord.ClosestHit;

	Hitrec rec1, rec2;

	rec1.ClosestHit = Infinity;
	rec2.ClosestHit = Infinity;

	/// Case-1: Check if entry point exists and store hit distance
	if (!Boundary->Hit(ray, rec1)) return false;
	hitDist1 = rec1.ClosestHit;

	// Create a new ray slightly offset from the first hit point to find exit point
	Ray offsetRay(ray.At((float)hitDist1 + 0.0001f), ray.Direction, ray.GetTime());

	/// Case-2: Check if the exit point exists using offset ray
	if (!Boundary->Hit(offsetRay, rec2)) return false;

	// Calculating the second hit distance including the offset
	hitDist2 = hitDist1 + 0.0001 + rec2.ClosestHit;
	hitrecord.ClosestHit = originalClosestHit;

	// Check if hits are in valid range
	if (hitDist1 < 0.0001) hitDist1 = 0.0001;
	if (hitDist2 > rayFarDist) hitDist2 = rayFarDist;

	/// Case-3: Check if hit points are in correct order and range
	if (hitDist1 >= hitDist2) return false;
	if (hitDist1 < 0.0) hitDist1 = 0.0;

	double rayLength = glm::length(ray.Direction);

	// Calculate random hit point using exponential distribution
	double hitDistance = NegInvDensity * std::log(Utils::RandomDouble());
	double distanceInside = (hitDist2 - hitDist1) * rayLength;

	/// Case-4: Check if the random hit point is within the volume
	if (hitDistance > distanceInside) return false;

	/// Case-5: Perfrom subsurface scatter and update hit record
	hitrecord.ClosestHit = hitDist1 + hitDistance / rayLength;
	hitrecord.HitPoint = ray.Origin + (float)hitrecord.ClosestHit * ray.Direction;
	hitrecord.SurfaceNormal = Utils::RandomUnitVector();
	hitrecord.FrontFace = true;
	hitrecord.MatId = PhaseFunction;

	return true;
}