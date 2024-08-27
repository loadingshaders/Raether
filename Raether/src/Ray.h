#pragma once

#include <glm\glm.hpp>

struct Ray {
	glm::vec3 Origin;
	glm::vec3 Direction;
	float Time;

	const float GetTime() const {
		return Time;
	}
};