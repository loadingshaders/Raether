#pragma once

#include <limits>

#include "Utils.h"

class Interval {
public:
	Interval() : Min(std::numeric_limits<float>::min()), Max(std::numeric_limits<float>::max()) { }
	Interval(float min, float max) : Min(min), Max(max) { }
	Interval(double min, double max) : Min((float)min), Max((float)max) { }
	Interval(const Interval& a, const Interval& b) {
		Min = (a.Min <= b.Min) ? a.Min : b.Min;
		Max = (a.Max >= b.Max) ? a.Max : b.Max;
	}

	const double Clamp(double val) const {
		if (val < Min) {
			return Min;
		}
		else if (val > Max) {
			return Max;
		}
		return val;
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
	const float Size() const {
		return Max - Min;
	}
	bool Contains(float val) const {
		return (Min <= val) && (val <= Max);
	}
	bool Contains(double val) const {
		return (Min <= val) && (val <= Max);
	}
	Interval Expand(float delta) {
		float padding = delta / 2.f;
		return Interval(Min - padding, Max + padding);
	}
	bool Surrounds(float val) const {
		return (Min < val) && (val < Max);
	}
	bool Surrounds(double val) const {
		return (Min < val) && (val < Max);
	}

public:
	float Min, Max;
	static const Interval Empty, Universe;
};

inline const Interval Interval::Empty = Interval(+Infinity, -Infinity);
inline const Interval Interval::Universe = Interval(-Infinity, +Infinity);

inline Interval operator+(const Interval& interval, const float& displacement) {
	return Interval(interval.Min + displacement, interval.Max + displacement);
}

inline Interval operator+(const float& displacement, const Interval& interval) {
	return interval + displacement;
}