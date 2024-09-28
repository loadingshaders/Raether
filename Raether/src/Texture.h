#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Image.h"
#include "Perlin.h"

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

class CheckerTexture : public Texture {
public:
	CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :
		InvScale(1.0 / scale),
		Even(even),
		Odd(odd)
	{}
	CheckerTexture(double scale, glm::vec3& color1, glm::vec3& color2) :
		CheckerTexture(scale, std::make_shared<SolidColor>(color1), std::make_shared<SolidColor>(color2))
	{}

	glm::vec3 value(double u, double v, glm::vec3& point) const override {
		int xInteger = int(glm::floor(InvScale * point.x));
		int yInteger = int(glm::floor(InvScale * point.y));
		int zInteger = int(glm::floor(InvScale * point.z));

		bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

		return isEven ? Even->value(u, v, point) : Odd->value(u, v, point);
	}

private:
	double InvScale;
	std::shared_ptr<Texture> Even;
	std::shared_ptr<Texture> Odd;
};

class ImageTexture : public Texture {
public:
	ImageTexture() : Img("UVChecker_2K.png") {}
	ImageTexture(const char* imagePath) : Img(imagePath) {}

	glm::vec3 value(double u, double v, glm::vec3& point) const override {

		// If no image is loaded return color-cyan
		if (Img.GetWidth() == 0) return glm::vec3(0.f, 1.f, 1.f);
		
		u = Interval(0.0, 1.0).Clamp(u);
		v = 1.0 - Interval(0.0, 1.0).Clamp(v);

		auto i = int(u * Img.GetWidth());
		auto j = int(v * Img.GetHeight());

		float colorScale = 1.f / 255.f;
		const unsigned char* pixel = Img.PixelData(i, j);

		return glm::vec3(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
	}

private:
	Image Img;
};

class NoiseTexture : public Texture {
public:
	NoiseTexture(double scale) : InvScale( 1.0 / scale){}

	glm::vec3 value(double u, double v, glm::vec3& point) const override {
		return glm::dvec3(1.0) * Noise.Noise(glm::dvec3(point) * InvScale);
	}

private:
	Perlin Noise;
	double InvScale;
};