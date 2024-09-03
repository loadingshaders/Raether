#pragma once

#include <iostream>
#include <chrono>

#define Timer
/// Clock
#define logtime std::chrono::steady_clock::now()
#define elapsed std::chrono::duration_cast<std::chrono::milliseconds>
#define clock std::chrono::steady_clock

namespace {
	int frameCount = 0;
	double totalTime = 0;

	clock::time_point start;
	clock::time_point end;
}