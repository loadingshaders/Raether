#include "Triangle.h"

Triangle::Triangle(const glm::dvec3& v0, const glm::dvec3& v1, const glm::dvec3& v2, std::shared_ptr<Material> matid) :
	V0(v0),
	V1(v1),
	V2(v2),
	MaterialId(matid)
{
	this->ObjectOrigin = (V0 + V1 + V2) / 3.0;
	this->ObjectMatId = MaterialId;

	/// Calculate edge vectors
	glm::dvec3 e1 = V1 - V0;
	glm::dvec3 e2 = V2 - V0;

	glm::dvec3 N = glm::cross(e1, e2);

	/// Calculate normal
	Normal = glm::normalize(N);

	/// Calculate plane equation constant D
	D = glm::dot(Normal, V0);

	/// Precompute inverse area for barycentric coordinate calculation
	double area = glm::length(N) * 0.5;
	W = N / (area * area * 2.0);

	/// Compute bounding box
	bbox = Aabb(
		glm::min(glm::min(V0, V1), V2),
		glm::max(glm::max(V0, V1), V2)
	);
}

bool Triangle::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
	/// Check for plane hit and update hitrecord

	/// Planar Equation
	/// Ax + By + Cz + D = 0  D => Constant
	/// Or, Ax + By + Cz = D
	/// We can also write,
	/// dot(normal, v) = D        normal => (A, B, C) And v => Vector from origin to any point on the plane

	/// Ray Equation => Ray Origin + Ray Direction * Distance =>  R(t) = Ro + t * Rd

	//     dot(normal, v) = D
	// or, dot(normal, (Ro + t * Rd)) = D     v => (Ro + t * Rd)
	// or, dot(normal, Ro) + dot(normal, t * Rd) = D
	// or, dot(normal, Ro) + t * dot(normal, Rd) = D
	// or, t * dot(normal, Rd) = D - dot(normal, Ro)
	// or, t = D - dot(normal, Ro) / dot(normal, Rd)

	double Denom = glm::dot(Normal, ray.Direction);

	/// Case-1: The Ray is Parallel to the Plane
	if (std::fabs(Denom) < 1e-8) return false;

	/// Case-2: If the Ray Hit Distance is outside the Ray Interval
	double t = (D - glm::dot(Normal, ray.Origin)) / Denom;

	if (!hitdist.Contains(t)) return false;

	/// Case-3: Check If the Ray Lies within the Planar Shape using it's Planar Co-ordinates
	glm::dvec3 hitPoint = ray.Origin + t * ray.Direction;

	// Compute Barycentric Coordinates
	glm::dvec3 v0 = V1 - V0;
	glm::dvec3 v1 = V2 - V0;
	glm::dvec3 v2 = hitPoint - V0;

	double dot00 = glm::dot(v0, v0);
	double dot01 = glm::dot(v0, v1);
	double dot02 = glm::dot(v0, v2);
	double dot11 = glm::dot(v1, v1);
	double dot12 = glm::dot(v1, v2);

	double InvDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
	double Alpha = (dot11 * dot02 - dot01 * dot12) * InvDenom;
	double Beta = (dot00 * dot12 - dot01 * dot02) * InvDenom;

	/// Case-4 Check if point is inside triangle
	if (!isInterior(Alpha, Beta, hitrecord)) return false;

	/// Case-5: Ray hits the 2D shape; set the rest of the hit record and return true
	hitrecord.ClosestHit = t;
	hitrecord.HitPoint = hitPoint;
	hitrecord.SurfaceNormal = Normal;
	hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
	hitrecord.HitPoint += hitrecord.SurfaceNormal * 0.000001;
	hitrecord.MatId = MaterialId;

	return true;
}

bool Triangle::isInterior(double u, double v, Hitrec& hitrecord) const {

	/// Check Barycentric Coordinates
	if (u < 0.0 || v < 0.0 || (u + v) > 1.0) return false;

	hitrecord.U = u;
	hitrecord.V = v;

	return true;
}