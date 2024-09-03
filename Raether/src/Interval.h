#pragma once

#pragma once

#include <limits>

class Interval {
public:
	Interval() : Min(std::numeric_limits<float>::min()), Max(std::numeric_limits<float>::max()) { }
	Interval(float min, float max) : Min(min), Max(max) { }
	Interval(const Interval& a, const Interval& b) {
		Min = (a.Min <= b.Min) ? a.Min : b.Min;
		Max = (a.Max >= b.Max) ? a.Max : b.Max;
	}

	const float Clamp(float val) const {
		if (val < Min) {
			return Min;
		}
		else if (val > Max) {
			return Max;
		}
		return val;
	}
	const float Size(float val) const {
		return Max - Min;
	}
	bool Contains(float val) const {
		return (val >= Min) && (val <= Max);
	}
	Interval Expand(float delta) {
		float padding = delta / 2.f;
		return Interval(Min - padding, Max + padding);
	}

public:
	float Min, Max;
};