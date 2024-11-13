#include "Quad.h"

Quad::Quad(const glm::vec3& q, const glm::vec3& u, const glm::vec3& v, std::shared_ptr<Material> matid) :
	Q(glm::dvec3(q)),
	U(glm::dvec3(u)),
	V(glm::dvec3(v)),
	MaterialId(matid)
{
	this->ObjectOrigin = glm::vec3(Q) + glm::vec3(U + V) * 0.5f;
	this->ObjectMatId = MaterialId;

	/// Calculate Normal And D
	glm::dvec3 N = glm::cross(U, V);
	Normal = glm::normalize(N);
	D = glm::dot(Normal, Q);
	W = N / glm::dot(N, N);

	/// Initialize the Bounding Volume for Quad
	Aabb bboxDiagonal1 = Aabb(glm::vec3(Q), glm::vec3(Q + U + V));
	Aabb bboxDiagonal2 = Aabb(glm::vec3(Q + U), glm::vec3(Q + V));
	bbox = Aabb(bboxDiagonal1, bboxDiagonal2);
}

bool Quad::Hit(const Ray& ray, Hitrec& hitrecord) const {
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

	double Denom = glm::dot(Normal, glm::dvec3(ray.Direction));

	/// Case-1: The Ray is Parallel to the Plane
	if (std::fabs(Denom) < 1e-8) return false;

	/// Case-2: If the Ray Hit Distance is outside the Ray Interval
	double t = (D - glm::dot(Normal, glm::dvec3(ray.Origin))) / Denom;
	
	if (!Interval(rayNearDist, hitrecord.ClosestHit).Contains(t)) return false;

	/// Case-3: Check If the Ray Lies within the Planar Shape using it's Planar Co-ordinates
	glm::dvec3 hitPoint = glm::dvec3(ray.Origin) + t * glm::dvec3(ray.Direction);
	
	glm::dvec3 planarHitPoint = hitPoint - Q;
	double Alpha = glm::dot(W, glm::cross(planarHitPoint, V));
	double Beta = glm::dot(W, glm::cross(U, planarHitPoint));

	if (!isInterior(Alpha, Beta, hitrecord)) return false;

	/// Case-4: Ray hits the 2D shape; set the rest of the hit record and return true
	hitrecord.HitPoint = glm::vec3(hitPoint);
	hitrecord.SurfaceNormal = glm::vec3(Normal);
	hitrecord.SetFrontFace(ray.Direction, hitrecord.SurfaceNormal);
	hitrecord.MatId = MaterialId;
	hitrecord.ClosestHit = t;

	return true;
}

bool Quad::isInterior(double a, double b, Hitrec& hitrecord) const {
	Interval unitInterval = Interval(0.0, 1.0);

	// Given the hit point in plane coordinates, return false if it is outside the
	// primitive, otherwise set the hit record UV coordinates and return true.

	if (!unitInterval.Contains(a) || !unitInterval.Contains(b)) return false;

	hitrecord.U = (float)glm::clamp(a, 0.0, 1.0);
	hitrecord.V = (float)glm::clamp(b, 0.0, 1.0);

	return true;
}