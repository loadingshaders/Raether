#pragma once

#include <glm\glm.hpp>

class Ray {
public:
	Ray() :
		Origin(glm::vec3(0.f)),
		Direction(glm::vec3(0.f, 0.f, -1.f)),
		Time(0.f)
	{}
	Ray(const glm::vec3& origin, const glm::vec3& direction, const float& time) :
		Origin(origin),
		Direction(direction),
		Time(time)
	{}

	const float GetTime() const {
		return Time;
	}

public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	float Time;
};