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

	double Noise(const glm::vec3& point) const {

		double u = point.x - glm::floor(point.x);
		double v = point.y - glm::floor(point.y);
		double w = point.z - glm::floor(point.z);

		// Hermitian Cubic Smoothing
		u = u * u * (3.0 - 2.0 * u);
		v = v * v * (3.0 - 2.0 * v);
		w = w * w * (3.0 - 2.0 * w);

		int i = int(glm::floor(point.x));
		int j = int(glm::floor(point.y));
		int k = int(glm::floor(point.z));

		double Lerp[2][2][2];

		for (int di = 0; di < 2; di++) {
			for (int dj = 0; dj < 2; dj++) {
				for (int dk = 0; dk < 2; dk++) {
					Lerp[di][dj][dk] = RandomDoubles[
						PermuteX[(i + di) & (TileWidth - 1)] ^
							PermuteY[(j + dj) & (TileWidth - 1)] ^
							PermuteZ[(k + dk) & (TileWidth - 1)]
					];
				}
			}
		}

		return TriLerp(&Lerp[0][0][0], 2, u, v, w);
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
	static double TriLerp(const double* lerp, int size, double u, double v, double w) {
		double Accum = 0.0;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					Accum +=
						(i * u + (1 - i) * (1 - u)) *
						(j * v + (1 - j) * (1 - v)) *
						(k * w + (1 - k) * (1 - w)) *
						lerp[i * size * size + j * size + k];
				}
			}
		}

		return Accum;
	}

private:
	static constexpr int TileWidth = 256;
	double RandomDoubles[TileWidth];
	int PermuteX[TileWidth];
	int PermuteY[TileWidth];
	int PermuteZ[TileWidth];
};