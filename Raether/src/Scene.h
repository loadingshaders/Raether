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