#pragma once

#include <iostream>

#include <glm\glm.hpp>

class Texture {
public:
	virtual ~Texture() = default;
	virtual glm::vec3 value(double u, double v, glm::vec3& point) const = 0;
};

class SolidColor : public Texture {
public:
	SolidColor(glm::vec3& color) : Albedo(color) {}
	SolidColor(float r, float g, float b) : SolidColor(glm::vec3(r, g, b)) {}

	glm::vec3 value(double u, double v, glm::vec3& point) const override {
		return Albedo;
	}
private:
	glm::vec3 Albedo;
};