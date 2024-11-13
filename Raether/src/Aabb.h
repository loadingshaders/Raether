#pragma once

#pragma once

#include <glm\glm.hpp>

#include "Interval.h"
#include "Ray.h"

class Aabb {
public:
	Interval x, y, z;
public:
	Aabb() { } // The default AABB is empty
	Aabb(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z) {
		PadToMinimum();
	}
	Aabb(const glm::vec3 a, const glm::vec3 b) {
		x = (a[0] <= b[0]) ? (Interval(a[0], b[0])) : (Interval(b[0], a[0]));
		y = (a[1] <= b[1]) ? (Interval(a[1], b[1])) : (Interval(b[1], a[1]));
		z = (a[2] <= b[2]) ? (Interval(a[2], b[2])) : (Interval(b[2], a[2]));

		PadToMinimum();
	}
	Aabb(const Aabb& box1, const Aabb& box2) {
		x = Interval(box1.x, box2.x);
		y = Interval(box1.y, box2.y);
		z = Interval(box1.z, box2.z);
	}

	const Interval& AxisInterval(int axis) const {
		if (axis == 1) return y;
		else if (axis == 2) return z;
		return x;
	}
	int LongestAxis() const {
		if (x.Size() > y.Size()) {
			return (x.Size() > z.Size()) ? 0 : 2;
		}
		else {
			return (y.Size() > z.Size()) ? 1 : 2;
		}
	}

	bool Hit(const Ray& ray, Interval& interval) const {
		const glm::vec3 rayOrigin = ray.Origin;
		const glm::vec3 rayDirection = ray.Direction;

		for (int axis = 0; axis < 3; axis++) {
			const Interval& axisInterval = AxisInterval(axis);
			float rayDirInv = 1.f / rayDirection[axis];

			float t0 = (axisInterval.Min - ray.Origin[axis]) * rayDirInv; // axisInterval.Min => x0
			float t1 = (axisInterval.Max - ray.Origin[axis]) * rayDirInv; // axisInterval.Max => x1

			if (t0 < t1) {
				if (t0 > interval.Min) interval.Min = t0; // interval.Min => t.Start
				if (t1 < interval.Max) interval.Max = t1; // interval.Max => t.End
			}
			else {
				if (t1 > interval.Min) interval.Min = t1;
				if (t0 < interval.Max) interval.Max = t0;
			}

			if (interval.Max <= interval.Min) { // If t.End <= t.Start means the object is behind the camera. So, not a hit.
				return false;
			}
		}

		return true;
	}

	void PadToMinimum() {
		// Adjusting the AABB so that no side is narrower than the value Delta

		float Delta = 0.0001f;
		if (x.Size() < Delta) x = x.Expand(Delta);
		if (y.Size() < Delta) y = y.Expand(Delta);
		if (z.Size() < Delta) z = z.Expand(Delta);
	}
};

inline Aabb operator+(const Aabb& bbox, const glm::vec3& offset) {
	return Aabb(bbox.x + offset.x, bbox.y + offset.y, bbox.z + offset.z);
}

inline Aabb operator+(const glm::vec3& offset, const Aabb& bbox) {
	return bbox + offset;
}