#pragma once

#include <iostream>

#include "Utils.h"

class Perlin {
public:
	Perlin() {

		for (int i = 0; i < TileWidth; i++) {
			RandomDoubles[i] = Utils::RandomDouble();
		}

		PerlinGenPermute(PermuteX);
		PerlinGenPermute(PermuteY);
		PerlinGenPermute(PermuteZ);
	}

	double Noise(const glm::vec3& point, double scale) const {

		int i = int(glm::floor(scale * point.x)) & (TileWidth - 1);
		int j = int(glm::floor(scale * point.y)) & (TileWidth - 1);
		int k = int(glm::floor(scale * point.z)) & (TileWidth - 1);

		return RandomDoubles[PermuteX[i] ^ PermuteY[j] ^ PermuteZ[k]];
	}

private:
	void PerlinGenPermute(int* p) {
		for (int i = 0; i < TileWidth; i++) {
			p[i] = i;
		}

		Permute(p, TileWidth);
	}
	void Permute(int* p, int count) {
		for (int i = count - 1; i >= 0; i--) {
			int target = Utils::RandomIntInRange(0, i);
			int temp = p[i];
			p[i] = p[target];
			p[target] = temp;
		}
	}

private:
	double Scale;
	static constexpr int TileWidth = 256;
	double RandomDoubles[TileWidth];
	int PermuteX[TileWidth];
	int PermuteY[TileWidth];
	int PermuteZ[TileWidth];
};