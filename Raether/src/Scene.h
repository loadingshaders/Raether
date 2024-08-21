#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>

#include "Utils.h"
#include "Ray.h"

#define near 0.001f
#define far 10000.f

struct Hitrec {
	glm::vec3 HitPoint;
	glm::vec3 SurfaceNormal;
	glm::vec3 HitColor;
	int HitObjId;
	bool FrontFace;

	void SetFrontFace(const glm::vec3& rayDirection, glm::vec3& normal) {
		if (glm::dot(rayDirection, normal) > 0.f) {
			FrontFace = false;
		}
		else {
			FrontFace = true;
		}
		normal = FrontFace ? (normal) : (-normal);
	}
};

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

		float ri = (hitrecord.FrontFace) ? (1.f / RefractionIndex) : (RefractionIndex);

		ray.Origin = hitrecord.HitPoint;
		// Dielectric refraction and reflections
		ray.Direction = glm::refract(glm::normalize(ray.Direction), hitrecord.SurfaceNormal, ri);

		attenuation = glm::vec3(1.f);
		return true;
	}

private:
	float RefractionIndex;
};

struct Sphere {
	glm::vec3 SphereOrigin{ 0.0f };
	float Radius = 0.5f;

	int MatIndex = 0;
};

struct Scene {

	uint32_t SampleCount;
	uint32_t Bounces;

	std::vector<Sphere> SphereList;
	std::vector<std::shared_ptr<Material>> Materials;

	void setSampleCount(uint32_t count) {
		SampleCount = count;
	}
	void setSampleBounces(uint32_t bounces) {
		Bounces = bounces;
	}
	void addSpheres(Sphere sphere) {
		SphereList.push_back(sphere);
	}
	void addMaterials(std::shared_ptr<Material> mat) {
		Materials.push_back(mat);
	}
};