#pragma once

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Texture.h"

class Material {
public:
	virtual ~Material() = default;

	virtual glm::dvec3 Emitted(double u, double v, glm::dvec3& point) const {
		return glm::dvec3(0.0);
	}

	virtual bool Scatter(Ray& ray, Hitrec& hitrecord, glm::dvec3& attenuation) const {
		return false;
	}
};

class Lambertian : public Material {
public:
	Lambertian(glm::dvec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) {}
	Lambertian(std::shared_ptr<Texture> texture) : Tex(texture) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::dvec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;

		/// Non Uniform Lambertian Diffuse Scattering
		ray.Direction = hitrecord.SurfaceNormal + Utils::RandomUnitVector();

		if (Utils::NearZero(ray.Direction)) {
			ray.Direction = hitrecord.SurfaceNormal;
		}

		ray.Time = ray.GetTime();

		attenuation = Tex->value(hitrecord.U, hitrecord.V, hitrecord.HitPoint);
		return true;
	}

private:
	std::shared_ptr<Texture> Tex;
};

class Metal : public Material {
public:
	Metal(glm::dvec3 albedo, double fuzzyness) : Albedo(albedo), Fuzzyness((fuzzyness < 1.0) ? ((fuzzyness < 0.0) ? 0.0 : fuzzyness) : 1.0) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::dvec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;

		/// Metal shiny and fuzzy reflection
		ray.Direction = glm::reflect(ray.Direction, hitrecord.SurfaceNormal);
		ray.Direction = glm::normalize(ray.Direction) + (Fuzzyness * Utils::RandomUnitVector());

		ray.Time = ray.GetTime();

		attenuation = Albedo;
		return (glm::dot(ray.Direction, hitrecord.SurfaceNormal) > 0);
	}

private:
	glm::dvec3 Albedo;
	double Fuzzyness;
};

class Dielectric : public Material {
public:
	Dielectric(double ri) : RefractionIndex(ri), Fuzzyness(0.0) {}
	Dielectric(double ri, double fuzzyness) : RefractionIndex(ri), Fuzzyness((fuzzyness < 1.0) ? ((fuzzyness < 0.0) ? 0.0 : fuzzyness) : 1.0) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::dvec3& attenuation) const override {

		double ri = (hitrecord.FrontFace) ? (1.0003 / RefractionIndex) : (RefractionIndex);

		glm::dvec3 unitDirection = glm::normalize(ray.Direction);

		double cosTheta = std::fmin(glm::dot(-unitDirection, hitrecord.SurfaceNormal), 1.0);
		double sinTheta = std::sqrt(1.0 - (cosTheta * cosTheta));

		bool cannotRefract = ((ri * sinTheta) > 1.0);

		ray.Origin = hitrecord.HitPoint;

		if (cannotRefract || Reflectance(cosTheta, ri) > Utils::RandomDouble()) {
			ray.Direction = glm::reflect(ray.Direction, hitrecord.SurfaceNormal);
		}
		else {
			// Dielectric refraction and reflections
			ray.Direction = glm::refract(unitDirection, hitrecord.SurfaceNormal, ri);
		}

		ray.Direction = glm::normalize(ray.Direction) + Fuzzyness * Utils::RandomUnitVector();
		ray.Time = ray.GetTime();

		attenuation = glm::dvec3(1.0);
		return true;
	}

private:
	double RefractionIndex;
	double Fuzzyness;

	static double Reflectance(double cosine, double ri) {
		// Using Schlick's approximation for reflectance.
		double r0 = (1.0 - ri) / (1.0 + ri);
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
	}
};

class DiffuseLight : public Material {
public:
	DiffuseLight(glm::dvec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) {}
	DiffuseLight(std::shared_ptr<Texture> texture) : Tex(texture) {}

	glm::dvec3 Emitted(double u, double v, glm::dvec3& point) const override {
		return Tex->value(u, v, point);
	}

private:
	std::shared_ptr<Texture> Tex;
};

class Isotropic : public Material {
public:
	Isotropic(glm::dvec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) {}
	Isotropic(std::shared_ptr<Texture> texture) : Tex(texture) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::dvec3& attenuation) const override {

		ray = Ray(hitrecord.HitPoint, Utils::RandomUnitVector(), ray.GetTime());

		attenuation = Tex->value(hitrecord.U, hitrecord.V, hitrecord.HitPoint);

		return true;
	}

private:
	std::shared_ptr<Texture> Tex;
};