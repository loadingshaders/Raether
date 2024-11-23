#pragma once

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"
#include "Hittable.h"
#include "Texture.h"

class Material {
public:
	virtual ~Material() = default;

	virtual glm::vec3 Emitted(double u, double v, glm::vec3& point) const {
		return glm::vec3(0.0f);
	}

	virtual bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const {
		return false;
	}
};

class Lambertian : public Material {
public:
	Lambertian(glm::vec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) { }
	Lambertian(std::shared_ptr<Texture> texture) : Tex(texture) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;
		// Non Uniform Lambertian Diffuse Scattering
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
	Metal(glm::vec3 albedo, float fuzzyness) : Albedo(albedo), Fuzzyness((fuzzyness < 1.0f)? ((fuzzyness < 0.0f)? 0.0f : fuzzyness) : 1.0f) { }

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		ray.Origin = hitrecord.HitPoint;

		/// Metal shiny and fuzzy reflection
		ray.Direction = glm::reflect(ray.Direction, hitrecord.SurfaceNormal);
		ray.Direction = glm::normalize(ray.Direction) + (Fuzzyness * Utils::RandomUnitVector());
		ray.Time = ray.GetTime();

		attenuation = Albedo;
		return (glm::dot(ray.Direction, hitrecord.SurfaceNormal) > 0);
	}

private:
	glm::vec3 Albedo;
	float Fuzzyness;
};

class Dielectric : public Material {
public:
	Dielectric(float ri) : RefractionIndex(ri), Fuzzyness(0.f) { }
	Dielectric(float ri, float fuzzyness) : RefractionIndex(ri), Fuzzyness(fuzzyness) { }

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

		ray.Direction = glm::normalize(ray.Direction) + Fuzzyness * Utils::RandomUnitVector();
		ray.Time = ray.GetTime();

		attenuation = glm::vec3(1.f);
		return true;
	}

private:
	float RefractionIndex;
	float Fuzzyness;

	static float Reflectance(float cosine, float ri) {
		// Using Schlick's approximation for reflectance.
		auto r0 = (1.f - ri) / (1.f + ri);
		r0 = r0 * r0;
		return r0 + (1.f - r0) * std::pow((1.f - cosine), 5.f);
	}
};

class DiffuseLight : public Material {
public:
	DiffuseLight(glm::vec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) {}
	DiffuseLight(std::shared_ptr<Texture> texture) : Tex(texture) {}

	glm::vec3 Emitted(double u, double v, glm::vec3& point) const override {
		return Tex->value(u, v, point);
	}

private:
	std::shared_ptr<Texture> Tex;
};

class Isotropic : public Material {
public:
	Isotropic(glm::vec3 albedo) : Tex(std::make_shared<SolidColor>(albedo)) {}
	Isotropic(std::shared_ptr<Texture> texture) : Tex(texture) {}

	bool Scatter(Ray& ray, Hitrec& hitrecord, glm::vec3& attenuation) const override {

		ray = Ray(hitrecord.HitPoint, Utils::RandomUnitVector(), ray.GetTime());
		
		attenuation = Tex->value(hitrecord.U, hitrecord.V, hitrecord.HitPoint);
		
		return true;
	}

private:
	std::shared_ptr<Texture> Tex;
};