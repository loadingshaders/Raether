#pragma once

#include "Utils.h"
#include "Ray.h"

class Material {
public:
	virtual ~Material() = default;

	virtual bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const {
		return false;
	}
};

class Lambertian : public Material {
public:
	Lambertian(glm::vec3 albedo) : Albedo(albedo) { }

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;
		// Non Uniform Lambertian Diffuse Scattering
		ray.Direction = hitrecord.SurfaceNormal + Utils::RandomUnitVector();

		if (Utils::NearZero(ray.Direction)) {
			ray.Direction = hitrecord.SurfaceNormal;
		}

		ray.Time = ray.GetTime();

		attenuation = Albedo;
		return true;
	}

private:
	glm::vec3 Albedo;
};

class Metal : public Material {
public:
	Metal(glm::vec3 albedo, float fuzzyness) : Albedo(albedo), Fuzzyness(fuzzyness) { }

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;
		// Metal shiny and fuzzy reflection
		ray.Direction = glm::reflect(ray.Direction, hitrecord.SurfaceNormal);
		ray.Direction = glm::normalize(ray.Direction) + Fuzzyness * Utils::RandomUnitVector();
		ray.Time = ray.GetTime();

		attenuation = Albedo;
		return true;
	}

private:
	glm::vec3 Albedo;
	float Fuzzyness;
};

class Dielectric : public Material {
public:
	Dielectric(float ri) : RefractionIndex(ri) { }

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		float ri = (hitrecord.FrontFace) ? (1.0003f / RefractionIndex) : (RefractionIndex);

		glm::vec3 unitDirection = glm::normalize(ray.Direction);

		float cosTheta = std::fmin(glm::dot(-unitDirection, hitrecord.SurfaceNormal), 1.f);
		float sinTheta = std::sqrt(1.f - (cosTheta * cosTheta));

		bool cannotRefract = ((ri * sinTheta) > 1.f);

		ray.Origin = hitrecord.HitPoint;

		if (cannotRefract || Reflectance(cosTheta, ri) > Utils::RandomFloat()) {
			ray.Direction = glm::reflect(ray.Direction, hitrecord.SurfaceNormal);
		}
		else {
			// Dielectric refraction and reflections
			ray.Direction = glm::refract(unitDirection, hitrecord.SurfaceNormal, ri);
		}

		ray.Time = ray.GetTime();

		attenuation = glm::vec3(1.f);
		return true;
	}

private:
	float RefractionIndex;

	static float Reflectance(float cosine, float ri) {
		// Using Schlick's approximation for reflectance.
		auto r0 = (1.f - ri) / (1.f + ri);
		r0 = r0 * r0;
		return r0 + (1.f - r0) * std::pow((1.f - cosine), 5.f);
	}
};