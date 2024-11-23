#pragma once

#include <iostream>
#include <string>
#include <random>

#include <SDL\SDL.h>
#include <glm\glm.hpp>

#include "Config.h"

namespace GLM {
	typedef glm::tvec4<uint8_t> ui8_tvec4;
	typedef glm::tvec4<uint16_t> ut16_tvec4;
	typedef glm::tvec2<int64_t> si32_tvec2;
}

namespace Utils {

	#ifndef DEBUG
	
	inline void PrintDvec2(const char* vecName, glm::dvec2 vec) {
		std::cout << vecName << " glm::dvec2(" << vec.r << ", " << vec.g << ")" << std::endl;
	}
	inline void PrintDvec3(const char* vecName, glm::dvec3 vec) {
		std::cout << vecName << " glm::dvec3(" << vec.r << ", " << vec.g << ", " << vec.b << ")" << std::endl;
	}
	inline void PrintDvec4(const char* vecName, glm::dvec4 vec) {
		std::cout << vecName << " glm::dvec4(" << vec.r << ", " << vec.g << ", " << vec.b << ", " << vec.a << ")" << std::endl;
	}
	inline void PrintVec2(const char* vecName, glm::vec2 vec) {
		std::cout << vecName << " glm::vec2(" << vec.r << ", " << vec.g << ")" << std::endl;
	}
	inline void PrintVec3(const char* vecName, glm::vec3 vec) {
		std::cout << vecName << " glm::vec3(" << vec.r << ", " << vec.g << ", " << vec.b << ")" << std::endl;
	}
	inline void PrintVec4(const char* vecName, glm::vec4 vec) {
		std::cout << vecName << " glm::vec4(" << vec.r << ", " << vec.g << ", " << vec.b << ", " << vec.a << ")" << std::endl;
	}
	inline void PrintError(std::string Error) {
		std::cout << Error << std::endl;
	}

	#else
	
	inline void PrintDvec2(const char* vecName, glm::dvec2 vec) {
		// Do Nothing!
	}
	inline void PrintDvec3(const char* vecName, glm::dvec3 vec) {
		// Do Nothing!
	}
	inline void PrintDvec4(const char* vecName, glm::dvec4 vec) {
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
	inline void PrintError(std::string Error) {
		// Do Nothing!
	}
	#endif
	
	inline double Inrange(double value, double low, double high) {
		return (value > low && value < high);
	}
	inline glm::dvec3 Lerp(const glm::dvec3& rayDirection, glm::dvec3 start, glm::dvec3 end) {
		double t = 1.0 - ((rayDirection.y * 0.5) + 0.5);

		/// Calculate linear color gradient using linear interpolation
		return glm::dvec3((1.0 - t) * start + t * end);
	}
	inline double GammaCorrect(double value) {
		if (value > 0.0) {
			return glm::sqrt(value);
		}

		return 0.0;
	}
	inline GLM::ui8_tvec4 converttoRGBA(glm::dvec4& color) {

		GLM::ui8_tvec4 c;

		color.r = GammaCorrect(color.r);
		color.g = GammaCorrect(color.g);
		color.b = GammaCorrect(color.b);
		color.a = GammaCorrect(color.a);

		c.r = (uint8_t)(glm::clamp(color.r, 0.0, 0.999999) * 255.0);
		c.g = (uint8_t)(glm::clamp(color.g, 0.0, 0.999999) * 255.0);
		c.b = (uint8_t)(glm::clamp(color.b, 0.0, 0.999999) * 255.0);
		c.a = (uint8_t)(glm::clamp(color.a, 0.0, 0.999999) * 255.0);

		return c;
	}
	inline double LengthSquared(glm::dvec3 vec) {
		return (vec.r * vec.r + vec.g * vec.g + vec.b * vec.b);
	}
	inline bool NearZero(glm::dvec3& rayDirection) {
		double s = 1e-8;
		return ((std::fabs(rayDirection.r) < s) && (std::fabs(rayDirection.g) < s) && (std::fabs(rayDirection.b) < s));
	}
	inline double RandomDouble() {
		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> distr(0.0, 1.0);

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
		return static_cast<int>(RandomDoubleInRange(static_cast<double>(min), static_cast<double>(max + 1.0)));
	}
	inline glm::dvec3 RandomOffset(double from, double to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> distr(from, to);

		return glm::dvec3(distr(generator), distr(generator), distr(generator));
	}
	inline glm::dvec3 RandomOffset1(double from, double to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> dist(from, to);

		return glm::dvec3(dist(generator), dist(generator), dist(generator));
	}
	inline glm::dvec3 RandomOffset2(double from, double to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> dist(from, to);

		return glm::dvec3(dist(generator), dist(generator), dist(generator));
	}
	inline glm::dvec3 RandomVector(double from, double to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<double> distr(from, to);

		return glm::dvec3(distr(generator), distr(generator), distr(generator));
	}
	inline glm::dvec3 RandomUnitVector() {

		glm::dvec3 rand_unit;

		while (true) {
			rand_unit = RandomOffset(-1.0, 1.0);
			if (LengthSquared(rand_unit) < 1.0) {
				break;
			}
		}

		return glm::normalize(rand_unit);
	}
	inline glm::dvec3 RandomOnHemisphere(const glm::dvec3& surfacenormal) {
		glm::dvec3 random = RandomUnitVector();

		if (glm::dot(random, surfacenormal) > 0.0) {
			return random;
		}
		else {
			return -random;
		}
	}
	inline glm::dvec2 RandomPointOnCircle() {
		double randAngle = RandomDouble() * 2.0 * PI;
		glm::dvec2 pointOnCircle = glm::dvec2(glm::cos(randAngle), glm::sin(randAngle));
		return pointOnCircle * glm::sqrt(RandomDouble());
	}
};