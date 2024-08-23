#pragma once

#include <string>
#include <random>

#include <glm\glm.hpp>

#define black glm::vec3(0.0f, 0.0f, 0.0f)
#define white glm::vec3(1.0f)
#define blue glm::vec3(0.5294f, 0.8078f, 0.9215f) // glm::vec3(0.5f, 0.7f, 1.0f)

#define nearDist 0.001f
#define farDist 10000.f

#define minFov 5.f
#define maxFov 180.f
#define camMotionSensitivity 0.01f
#define camMovementSpeed 0.3f

namespace glm {
	typedef tvec4<uint8_t> ui8_tvec4;
	typedef tvec2<Sint32> si32_tvec2;
}

namespace Utils {

	#define PI 3.1415f

	#ifndef DEBUG
	inline void PrintError(std::string Error) {
		std::cout << Error << std::endl;
	}
	inline void PrintVec2(const char* vecName, glm::vec2 vec) {
		std::cout << vecName << std::endl;
		std::cout << "X => " << vec.r << std::endl;
		std::cout << "Y => " << vec.g << std::endl;
}
	inline void PrintVec3(const char* vecName, glm::vec3 vec) {
		std::cout << vecName << std::endl;
		std::cout << "X => " << vec.r << std::endl;
		std::cout << "Y => " << vec.g << std::endl;
		std::cout << "Z => " << vec.b << std::endl;
	}
	inline void PrintVec4(const char* vecName, glm::vec4 vec) {
		std::cout << vecName << std::endl;
		std::cout << "X => " << vec.r << std::endl;
		std::cout << "Y => " << vec.g << std::endl;
		std::cout << "Z => " << vec.b << std::endl;
		std::cout << "W => " << vec.a << std::endl;
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
	inline glm::ui8_tvec4 converttoRGBA(glm::vec4& color) {

		glm::ui8_tvec4 c;

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

	inline float RandomFloat() {
		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> distr(0.f, 1.f);
		
		return distr(generator);
	}
	inline double RandomFloatInRange(float min, float max) {
		return min + (max - min) * RandomFloat();
	}
	inline glm::vec3 RandomOffset(float from, float to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> distr(from, to);

		glm::vec3 offset(distr(generator), distr(generator), distr(generator));

		return offset;
	}
	inline glm::vec3 RandomOffset1(float from, float to) {

		std::random_device rand_dev;
		// Using Mersenne Twister algorithm for random num generation
		static std::mt19937 generator(rand_dev());
		static std::uniform_real_distribution<float> dist(from, to);

		glm::vec3 offset(dist(generator), dist(generator), dist(generator));

		return offset;
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
		float randAngle = RandomFloat() * 2.f * PI;
		glm::vec2 pointOnCircle = glm::vec2(glm::cos(randAngle), glm::sin(randAngle));
		return pointOnCircle * glm::sqrt(RandomFloat());
	}
};