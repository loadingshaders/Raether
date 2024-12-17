#pragma once

#include <glm\glm.hpp>

class Ray {
public:
	Ray() :
		Origin(glm::dvec3(0.0)),
		Direction(glm::dvec3(0.0, 0.0, -1.0)),
		Time(0.0)
	{}
	Ray(const glm::dvec3& origin, const glm::dvec3& direction, const double& time) :
		Origin(origin),
		Direction(direction),
		Time(time)
	{}

	const double GetTime() const {
		return Time;
	}

	glm::dvec3 At(double distance) const {
		return Origin + distance * Direction;
	}

public:
	glm::dvec3 Origin;
	glm::dvec3 Direction;
	double Time;
};