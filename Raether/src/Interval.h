#pragma once

#include <limits>

#include "Utils.h"

class Interval {
public:
	Interval() : Min(std::numeric_limits<double>::min()), Max(std::numeric_limits<double>::max()) {}
	Interval(double min, double max) : Min(min), Max(max) {}
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
	const double Size() const {
		return Max - Min;
	}
	bool Contains(double val) const {
		return (Min <= val) && (val <= Max);
	}
	Interval Expand(double delta) {
		double padding = delta / 2.0;
		return Interval(Min - padding, Max + padding);
	}
	bool Surrounds(double val) const {
		return (Min < val) && (val < Max);
	}

public:
	double Min, Max;
	static const Interval Empty, Universe;
};

inline const Interval Interval::Empty = Interval(+Infinity, -Infinity);
inline const Interval Interval::Universe = Interval(-Infinity, +Infinity);

inline Interval operator+(const Interval& interval, const double& displacement) {
	return Interval(interval.Min + displacement, interval.Max + displacement);
}

inline Interval operator+(const double& displacement, const Interval& interval) {
	return interval + displacement;
}