#include "Sphere.h"

Sphere::Sphere(glm::dvec3 origin, double radius, std::shared_ptr<Material> matid) :
	SphereOrigin(origin),
	Radius(radius),
	MaterialId(matid),
	IsMoving(false)
{
	this->ObjectOrigin = SphereOrigin;
	this->ObjectMatId = MaterialId;

	/// Initialize the Bounding Volume for Stationary Sphere
	glm::dvec3 rvec = glm::dvec3(Radius, Radius, Radius);
	bbox = Aabb(origin - rvec, origin + rvec);
}

Sphere::Sphere(glm::dvec3 origin1, glm::dvec3 origin2, double radius, std::shared_ptr<Material> matid) :
	SphereOrigin(origin1),
	Radius(radius),
	MaterialId(matid),
	IsMoving(true)
{
	this->ObjectOrigin = SphereOrigin;
	this->ObjectMatId = MaterialId;

	SphereMotion = origin2 - origin1;

	/// Initialize the Bounding Volume for Non-Stationary Sphere
	glm::dvec3 rvec = glm::dvec3(Radius, Radius, Radius);
	Aabb bbox1 = Aabb(origin1 - rvec, origin1 + rvec);
	Aabb bbox2 = Aabb(origin2 - rvec, origin2 + rvec);
	bbox = Aabb(bbox1, bbox2);
}

const glm::dvec3 Sphere::GetSphereOrigin(double time) const {
	// Linearly interpolate from center1 to center2 according to time,
	// Where time = 0 yields Origin1, and time = 1 yields Origin2
	return SphereOrigin + time * SphereMotion;
}

bool Sphere::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
	/// Check for sphere hit and update hitrecord

	/// Sphere Equation
	/// (bx^2 + by^2 + bz^2)t^2 + 2t (ax*bx + ay*by + az*bz) + (ax^2 + ay^2 + az^2) - r^2 = 0
	// a = camera/ray origin (ax, ay, az)
	// b = ray direction (bx, by, bz)
	// t = hit distance
	// A , B , C = sphere origin
	// r = sphere radius

	glm::dvec3 sphereOrigin = (IsMoving) ? GetSphereOrigin(ray.GetTime()) : SphereOrigin;
	glm::dvec3 newrayOrigin = sphereOrigin - ray.Origin;

	double a = Utils::LengthSquared(ray.Direction); // (bx^2 + by^2 + bz^2)
	double b = glm::dot(ray.Direction, newrayOrigin); // 2 (ax * bx + ay * by + az * bz)
	double c = Utils::LengthSquared(newrayOrigin) - (Radius * Radius); // (ax^2 + ay^2 + az^2) - r^2

	/// Case-1: Calculate if the ray hits the sphere or not
	double discriminant = (b * b) - (a * c);
	if (discriminant < 0.0) return false;

	double sqrtd = std::sqrt(discriminant);

	/// Case-2: Check if the hit distance is in the valid range
	double nearHit = (b - sqrtd) / a;
	if (!hitdist.Surrounds(nearHit)) {
		nearHit = (b + sqrtd) / a;
		if (!hitdist.Surrounds(nearHit)) {
			return false;
		}
	}

	/// Case-3: Ray hits the Sphere; set the rest of the hit record and return true
	hitrecord.ClosestHit = nearHit;
	hitrecord.HitPoint = ray.Origin + hitrecord.ClosestHit * ray.Direction;
	hitrecord.SurfaceNormal = (hitrecord.HitPoint - sphereOrigin) / Radius;
	hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
	hitrecord.HitPoint += hitrecord.SurfaceNormal * 0.000001;
	GetSphereUV(hitrecord.SurfaceNormal, hitrecord.U, hitrecord.V);
	hitrecord.MatId = MaterialId;

	return true;
}

void Sphere::GetSphereUV(const glm::dvec3& point, double& u, double& v) {
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