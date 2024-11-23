#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Image.h"
#include "Perlin.h"

class Texture {
public:
	virtual ~Texture() = default;
	virtual glm::dvec3 value(double u, double v, glm::dvec3& point) const = 0;
};

class SolidColor : public Texture {
public:
	SolidColor(glm::dvec3& color) : Albedo(color) {}
	SolidColor(double r, double g, double b) : SolidColor(glm::dvec3(r, g, b)) {}

	glm::dvec3 value(double u, double v, glm::dvec3& point) const override {
		return Albedo;
	}
private:
	glm::dvec3 Albedo;
};

class CheckerTexture : public Texture {
public:
	CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) :
		InvScale(1.0 / scale),
		Even(even),
		Odd(odd)
	{}
	CheckerTexture(double scale, glm::dvec3& color1, glm::dvec3& color2) :
		CheckerTexture(scale, std::make_shared<SolidColor>(color1), std::make_shared<SolidColor>(color2))
	{}

	glm::dvec3 value(double u, double v, glm::dvec3& point) const override {
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

	glm::dvec3 value(double u, double v, glm::dvec3& point) const override {

		// If no image is loaded return color-cyan
		if (Img.GetWidth() == 0) return glm::dvec3(0.0, 1.0, 1.0);

		u = Interval(0.0, 1.0).Clamp(u);
		v = 1.0 - Interval(0.0, 1.0).Clamp(v);

		auto i = int(u * Img.GetWidth());
		auto j = int(v * Img.GetHeight());

		double colorScale = 1.0 / 255.0;
		const unsigned char* pixel = Img.PixelData(i, j);

		return glm::dvec3(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
	}

private:
	Image Img;
};

class NoiseTexture : public Texture {
public:
	NoiseTexture(double scale) : InvScale(1.0 / scale) {}

	glm::dvec3 value(double u, double v, glm::dvec3& point) const override {
		return glm::dvec3(0.5) * (1.0 + glm::sin(InvScale * point.z + 10 * Noise.Turbulence(glm::dvec3(point), 7)));
	}

private:
	Perlin Noise;
	double InvScale;
};