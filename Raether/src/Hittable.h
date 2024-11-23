#pragma once

#include "Ray.h"
#include "Aabb.h"

class Material;

class Hitrec {
public:
	glm::dvec3 HitPoint;
	glm::dvec3 SurfaceNormal;
	glm::dvec3 HitColor;

	double ClosestHit;
	double U, V;
	
	bool FrontFace;

	std::shared_ptr<Material> MatId;

	void SetFrontFace(const glm::dvec3& rayDirection, glm::dvec3& normal) {
		FrontFace = glm::dot(rayDirection, normal) < 0.0;
		normal = FrontFace ? (normal) : (-normal);
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const = 0;
	virtual Aabb BoundingBox() const = 0;

public:
	glm::dvec3 ObjectOrigin;
	std::shared_ptr<Material> ObjectMatId;
};

class Translate : public Hittable {
public:
	Translate(std::shared_ptr<Hittable> object, const glm::dvec3& offset) :
		Object(object),
		Offset(offset)
	{
		bbox = Object->BoundingBox() + Offset;
	}

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override {
		/// Move the Ray Backwards by the Offset
		Ray offsetRay(ray.Origin - Offset, ray.Direction, ray.Time);

		/// Determine whether an intersection exists along the offset ray (and if so, where)
		if (!Object->Hit(offsetRay, hitdist, hitrecord)) return false;
		hitrecord.HitPoint += Offset;

		return true;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	std::shared_ptr<Hittable> Object;
	glm::dvec3 Offset;
	Aabb bbox;
};

class RotateX : public Hittable {
public:
	RotateX(std::shared_ptr<Hittable> object, const double& angle) :
		Object(object),
		Radians(glm::radians(angle))
	{
		SinTheta = std::sin(Radians);
		CosTheta = std::cos(Radians);

		bbox = Object->BoundingBox();

		glm::dvec3 Min = glm::dvec3(Infinity);
		glm::dvec3 Max = glm::dvec3(-Infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					double x = i * bbox.x.Max + (1 - i) * bbox.x.Min;
					double y = j * bbox.y.Max + (1 - j) * bbox.y.Min;
					double z = k * bbox.z.Max + (1 - k) * bbox.z.Min;

					double newy = CosTheta * y - SinTheta * z;
					double newz = SinTheta * y + CosTheta * z;

					glm::dvec3 tester(x, newy, newz);

					for (int c = 0; c < 3; c++) {
						Min[c] = std::fmin(Min[c], tester[c]);
						Max[c] = std::fmax(Max[c], tester[c]);
					}
				}
			}
		}

		bbox = Aabb(Min, Max);
	}

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override {
		/// Transform the ray from world space to object space
		glm::dvec3 Origin = glm::dvec3(
			(ray.Origin.x),
			(CosTheta * ray.Origin.y) + (SinTheta * ray.Origin.z),
			-(SinTheta * ray.Origin.y) + (CosTheta * ray.Origin.z)
		);

		glm::dvec3 Direction = glm::dvec3(
			(ray.Direction.x),
			(CosTheta * ray.Direction.y) + (SinTheta * ray.Direction.z),
			-(SinTheta * ray.Direction.y) + (CosTheta * ray.Direction.z)
		);

		Ray rotatedRay(Origin, Direction, ray.Time);

		/// Determine whether an intersection exists in object space (and if so, where)
		if (!Object->Hit(rotatedRay, hitdist, hitrecord)) return false;

		/// Transform the intersection from object space back to world space
		hitrecord.HitPoint = glm::dvec3(
			(hitrecord.HitPoint.x),
			(CosTheta * hitrecord.HitPoint.y) - (SinTheta * hitrecord.HitPoint.z),
			(SinTheta * hitrecord.HitPoint.y) + (CosTheta * hitrecord.HitPoint.z)
		);

		hitrecord.SurfaceNormal = glm::dvec3(
			(hitrecord.SurfaceNormal.x),
			(CosTheta * hitrecord.SurfaceNormal.y) - (SinTheta * hitrecord.SurfaceNormal.z),
			(SinTheta * hitrecord.SurfaceNormal.y) + (CosTheta * hitrecord.SurfaceNormal.z)
		);

		return true;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	std::shared_ptr<Hittable> Object;
	double Radians;
	double SinTheta, CosTheta;
	Aabb bbox;
};

class RotateY : public Hittable {
public:
	RotateY(std::shared_ptr<Hittable> object, const double& angle) :
		Object(object),
		Radians(glm::radians(angle))
	{
		SinTheta = std::sin(Radians);
		CosTheta = std::cos(Radians);

		bbox = Object->BoundingBox();

		glm::dvec3 Min = glm::dvec3(Infinity);
		glm::dvec3 Max = glm::dvec3(-Infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					double x = i * bbox.x.Max + (1 - i) * bbox.x.Min;
					double y = j * bbox.y.Max + (1 - j) * bbox.y.Min;
					double z = k * bbox.z.Max + (1 - k) * bbox.z.Min;

					double newx = CosTheta * x + SinTheta * z;
					double newz = -SinTheta * x + CosTheta * z;

					glm::dvec3 tester(newx, y, newz);

					for (int c = 0; c < 3; c++) {
						Min[c] = std::fmin(Min[c], tester[c]);
						Max[c] = std::fmax(Max[c], tester[c]);
					}
				}
			}
		}

		bbox = Aabb(Min, Max);
	}

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override {
		/// Transform the ray from world space to object space
		glm::dvec3 Origin = glm::dvec3(
			(CosTheta * ray.Origin.x) - (SinTheta * ray.Origin.z),
			(ray.Origin.y),
			(SinTheta * ray.Origin.x) + (CosTheta * ray.Origin.z)
		);

		glm::dvec3 Direction = glm::dvec3(
			(CosTheta * ray.Direction.x) - (SinTheta * ray.Direction.z),
			(ray.Direction.y),
			(SinTheta * ray.Direction.x) + (CosTheta * ray.Direction.z)
		);

		Ray rotatedRay(Origin, Direction, ray.Time);

		/// Determine whether an intersection exists in object space (and if so, where)
		if (!Object->Hit(rotatedRay, hitdist, hitrecord)) return false;

		/// Transform the intersection from object space back to world space
		hitrecord.HitPoint = glm::dvec3(
			(CosTheta * hitrecord.HitPoint.x) + (SinTheta * hitrecord.HitPoint.z),
			(hitrecord.HitPoint.y),
			(-SinTheta * hitrecord.HitPoint.x) + (CosTheta * hitrecord.HitPoint.z)
		);

		hitrecord.SurfaceNormal = glm::dvec3(
			(CosTheta * hitrecord.SurfaceNormal.x) + (SinTheta * hitrecord.SurfaceNormal.z),
			(hitrecord.SurfaceNormal.y),
			(-SinTheta * hitrecord.SurfaceNormal.x) + (CosTheta * hitrecord.SurfaceNormal.z)
		);

		return true;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	std::shared_ptr<Hittable> Object;
	double Radians;
	double SinTheta, CosTheta;
	Aabb bbox;
};

class RotateZ : public Hittable {
public:
	RotateZ(std::shared_ptr<Hittable> object, const double& angle) :
		Object(object),
		Radians(glm::radians(angle))
	{
		SinTheta = std::sin(Radians);
		CosTheta = std::cos(Radians);

		bbox = Object->BoundingBox();

		glm::dvec3 Min = glm::dvec3(Infinity);
		glm::dvec3 Max = glm::dvec3(-Infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					double x = i * bbox.x.Max + (1 - i) * bbox.x.Min;
					double y = j * bbox.y.Max + (1 - j) * bbox.y.Min;
					double z = k * bbox.z.Max + (1 - k) * bbox.z.Min;

					double newx = CosTheta * x - SinTheta * y;
					double newy = SinTheta * x + CosTheta * y;

					glm::dvec3 tester(newx, newy, z);

					for (int c = 0; c < 3; c++) {
						Min[c] = std::fmin(Min[c], tester[c]);
						Max[c] = std::fmax(Max[c], tester[c]);
					}
				}
			}
		}

		bbox = Aabb(Min, Max);
	}

	bool Hit(const Ray& ray, Interval hitdist, Hitrec& hitrecord) const override {

		/// Transform the ray from world space to object space
		glm::dvec3 Origin = glm::dvec3(
			(CosTheta * ray.Origin.x) + (SinTheta * ray.Origin.y),
			(-SinTheta * ray.Origin.x) + (CosTheta * ray.Origin.y),
			(ray.Origin.z)
		);

		glm::dvec3 Direction = glm::dvec3(
			(CosTheta * ray.Direction.x) + (SinTheta * ray.Direction.y),
			(-SinTheta * ray.Direction.x) + (CosTheta * ray.Direction.y),
			(ray.Direction.z)
		);

		Ray rotatedRay(Origin, Direction, ray.Time);

		/// Determine whether an intersection exists in object space (and if so, where)
		if (!Object->Hit(rotatedRay, hitdist, hitrecord)) return false;

		/// Transform the intersection from object space back to world space
		hitrecord.HitPoint = glm::dvec3(
			(CosTheta * hitrecord.HitPoint.x) - (SinTheta * hitrecord.HitPoint.y),
			(SinTheta * hitrecord.HitPoint.x) + (CosTheta * hitrecord.HitPoint.y),
			(hitrecord.HitPoint.z)
		);

		hitrecord.SurfaceNormal = glm::dvec3(
			(CosTheta * hitrecord.SurfaceNormal.x) - (SinTheta * hitrecord.SurfaceNormal.y),
			(SinTheta * hitrecord.SurfaceNormal.x) + (CosTheta * hitrecord.SurfaceNormal.y),
			(hitrecord.SurfaceNormal.z)
		);

		return true;
	}

	Aabb BoundingBox() const override { return bbox; }

private:
	std::shared_ptr<Hittable> Object;
	double Radians;
	double SinTheta, CosTheta;
	Aabb bbox;
};