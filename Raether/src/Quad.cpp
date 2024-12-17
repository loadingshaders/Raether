#include "Quad.h"

Quad::Quad(const glm::dvec3& q, const glm::dvec3& u, const glm::dvec3& v, std::shared_ptr<Material> matid) :
	Q(q),
	U(u),
	V(v),
	MaterialId(matid)
{
	this->ObjectOrigin = Q + ((U + V) * 0.5);
	this->ObjectMatId = MaterialId;

	/// Calculate Normal And D
	glm::dvec3 N = glm::cross(U, V);
	Normal = glm::normalize(N);
	D = glm::dot(Normal, Q);
	W = N / glm::dot(N, N);

	/// Initialize the Bounding Volume for Quad
	Aabb bboxDiagonal1 = Aabb(Q, Q + U + V);
	Aabb bboxDiagonal2 = Aabb(Q + U, Q + V);
	bbox = Aabb(bboxDiagonal1, bboxDiagonal2);
}

bool Quad::Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const {
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

	glm::dvec3 planarHitPoint = hitPoint - Q;
	double Alpha = glm::dot(W, glm::cross(planarHitPoint, V));
	double Beta = glm::dot(W, glm::cross(U, planarHitPoint));

	if (!isInterior(Alpha, Beta, hitrecord)) return false;

	/// Case-4: Ray hits the 2D shape; set the rest of the hit record and return true
	hitrecord.ClosestHit = t;
	hitrecord.HitPoint = hitPoint;
	hitrecord.SurfaceNormal = Normal;
	hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
	hitrecord.HitPoint += hitrecord.SurfaceNormal * 0.000001;
	hitrecord.MatId = MaterialId;

	return true;
}

bool Quad::isInterior(double u, double v, Hitrec& hitrecord) const {
	Interval unitInterval = Interval(0.0, 1.0);

	// Given the hit point in plane coordinates, return false if it is outside the
	// primitive, otherwise set the hit record UV coordinates and return true.

	if (!unitInterval.Contains(u) || !unitInterval.Contains(v)) return false;

	hitrecord.U = glm::clamp(u, 0.0, 1.0);
	hitrecord.V = glm::clamp(v, 0.0, 1.0);

	return true;
}