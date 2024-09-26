#pragma once

#include <iostream>

#include "Utils.h"

class Perlin {
public:
	Perlin() {

		for (int i = 0; i < TileWidth; i++) {
			for (int j = 0; j < TileWidth; j++) {
				for (int k = 0; k < TileWidth; k++) {
					RandomDoubles[i][j][k] = Utils::RandomDouble();
				}
			}
		}
	}

	double Noise(const glm::vec3& point, double scale) const {

		int i = int(scale * point.x) & (TileWidth - 1);
		int j = int(scale * point.y) & (TileWidth - 1);
		int k = int(scale * point.z) & (TileWidth - 1);

		return RandomDoubles[i][j][k];
	}

private:
	static constexpr int TileWidth = 4;
	double RandomDoubles[TileWidth][TileWidth][TileWidth];
	double Scale;
};