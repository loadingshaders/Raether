#pragma once

#include <iostream>
#include <string>
#include <random>

#include <SDL\SDL.h>
#include <glm\glm.hpp>

#include "Config.h"

namespace GLM {
	typedef glm::tvec4<uint8_t> ui8_tvec4;
	typedef glm::tvec2<int32_t> si32_tvec2;
}

namespace Utils {

	#define PI 3.14159265359

	#ifndef DEBUG
	inline void PrintError(std::string Error) {
		std::cout << Error << std::endl;
	}
	inline void PrintVec2(const char* vecName, glm::vec2 vec) {
		std::cout << vecName << std::endl;
		std::cout << "(X, Y) => " << vec.r << ", " << vec.g << std::endl;
	}
	inline void PrintVec3(const char* vecName, glm::vec3 vec) {
		std::cout << vecName << std::endl;
		std::cout << "(X, Y, Z) => " << vec.r << ", " << vec.g << ", " << vec.b << std::endl;
	}
	inline void PrintVec4(const char* vecName, glm::vec4 vec) {
		std::cout << vecName << std::endl;
		std::cout << "(X, Y, Z, W) => " << vec.r << ", " << vec.g << ", " << vec.b << ", " << vec.a << std::endl;
	}
	#else
	inline void PrintError(std::string Error) {
		// Do Nothing!
	}
	inline void PrintVec2(const char* vecName, glm::vec2 vec) {
		// Do Nothing!
	}
	inline void PrintVec3(const char* vecName, glm::vec3 vec) {
		// Do Nothing!
	}
	inline void PrintVec4(const char* vecName, glm::vec4 vec) {
		// Do Nothing!
	}
	#endif
	
	inline bool Inrange(float value, float low, float high) {
		if (value > low && value < high) {
			return true;
		}
		return false;
	}
	inline bool Inrange(double value, double low, double high) {
		if (value > low && value < high) {
			return true;
		}
		return false;
	}
	inline glm::vec3 Lerp(const glm::vec3& rayDirection, glm::vec3 start, glm::vec3 end) {
		float t = 1.0f - ((rayDirection.y * 0.5f) + 0.5f);
		/// Calculate linear color gradient using linear interpolation
		return glm::vec3((1 - t) * start + t * end);
	}
	inline float GammaCorrect(float value) {
		if (value > 0.f) {
			return glm::sqrt(value);
		}

		return 0.f;
	}
	inline GLM::ui8_tvec4 converttoRGBA(glm::vec4& color) {

		GLM::ui8_tvec4 c;

		color.r = GammaCorrect(color.r);
		color.g = GammaCorrect(color.g);
		color.b = GammaCorrect(color.b);
		color.a = GammaCorrect(color.a);

		c.r = (uint8_t)(glm::clamp(color.r, 0.f, 0.999f) * 255.0f);
		c.g = (uint8_t)(glm::clamp(color.g, 0.f, 0.999f) * 255.0f);
		c.b = (uint8_t)(glm::clamp(color.b, 0.f, 0.999f) * 255.0f);
		c.a = (uint8_t)(glm::clamp(color.a, 0.f, 0.999f) * 255.0f);

		return c;
	}
	inline float LengthSquared(glm::vec3 vec) {
		return (vec.r * vec.r + vec.g * vec.g + vec.b * vec.b);
	}
	inline bool NearZero(glm::vec3& rayDirection) {
		double s = 1e-8;
		return ((std::fabs(rayDirection.r) < s) && (std::fabs(rayDirection.g) < s) && (std::fabs(rayDirection.b) < s));
	}

	inline double RandomDouble() {
		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> distr(0.f, 1.f);

		return distr(generator);
	}
	inline double RandomDoubleInRange(double min, double max) {
		return min + (max - min) * RandomDouble();
	}
	inline float RandomFloat() {
		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> distr(0.f, 1.f);
		
		return distr(generator);
	}
	inline float RandomFloatInRange(float min, float max) {
		return min + (max - min) * RandomFloat();
	}
	inline int RandomIntInRange(int min, int max) {
		// Use static_cast to ensure type safety
		return static_cast<int>(RandomFloatInRange(static_cast<float>(min), static_cast<float>(max + 1)));
	}
	inline glm::vec3 RandomOffset(float from, float to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> distr(from, to);

		return glm::vec3(distr(generator), distr(generator), distr(generator));
	}
	inline glm::vec3 RandomOffset1(float from, float to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> dist(from, to);

		return glm::vec3(dist(generator), dist(generator), dist(generator));
	}
	inline glm::dvec3 RandomVector(double from, double to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> distr(from, to);

		return glm::dvec3(distr(generator), distr(generator), distr(generator));
	}
	inline glm::vec3 RandomUnitVector() {

		glm::vec3 rand_unit;

		while (true) {
			rand_unit = RandomOffset(-1.f, 1.f);
			if (LengthSquared(rand_unit) < 1.f) {
				break;
			}
		}

		return glm::normalize(rand_unit);
	}
	inline glm::vec3 RandomOnHemisphere(const glm::vec3& surfacenormal) {
		glm::vec3 random = RandomUnitVector();

		if (glm::dot(random, surfacenormal) > 0.f) {
			return random;
		}
		else {
			return -random;
		}
	}
	inline glm::vec2 RandomPointOnCircle() {
		float randAngle = RandomFloat() * 2.f * float(PI);
		glm::vec2 pointOnCircle = glm::vec2(glm::cos(randAngle), glm::sin(randAngle));
		return pointOnCircle * glm::sqrt(RandomFloat());
	}
};