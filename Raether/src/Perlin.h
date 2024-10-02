#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Utils.h"

class Perlin {
public:
	Perlin() {

		for (int i = 0; i < TileWidth; i++) {
			RandomDoubles[i] = Utils::RandomVector(-1.0, 1.0);
		}

		PerlinGenPermute(PermuteX);
		PerlinGenPermute(PermuteY);
		PerlinGenPermute(PermuteZ);
	}

	double Noise(const glm::vec3& point) const {

		// Storing the Fractional Part
		double u = point.x - glm::floor(point.x);
		double v = point.y - glm::floor(point.y);
		double w = point.z - glm::floor(point.z);

		// Storing the Integer Part
		int i = int(glm::floor(point.x));
		int j = int(glm::floor(point.y));
		int k = int(glm::floor(point.z));

		// Array to hold random values for the lattice points
		glm::dvec3 Lerp[2][2][2];

		// Populating each lattice point with a random value
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

		return PerlinInterp(&Lerp[0][0][0], 2, u, v, w);
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
						((1 - u) * (1 - i) + u * i) * // Lero(u, v0, v1) = (1-u) * v0 + u * v1 => Lerp(u, 1-i, i) => (1-u) * (1-i) + u * i
						((1 - v) * (1 - j) + v * j) * // Lero(v, v0, v1) = (1-v) * v0 + v * v1 => Lerp(v, 1-j, j) => (1-v) * (1-j) + v * j
						((1 - w) * (1 - k) + w * k) * // Lero(w, v0, v1) = (1-w) * v0 + w * v1 => Lerp(w, 1-k, k) => (1-w) * (1-k) + w * k
						lerp[i * size * size + j * size + k];
				}
			}
		}

		return Accum;
	}

	static double PerlinInterp(const glm::dvec3* lerp, int size, double u, double v, double w) {

		// Hermitian Cubic Smoothing
		double uu = u * u * (3.0 - 2.0 * u);
		double vv = v * v * (3.0 - 2.0 * v);
		double ww = w * w * (3.0 - 2.0 * w);

		double Accum = 0.0;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					glm::dvec3 Weight = glm::dvec3(u - i, v - j, w - k); // Here, i, j, k represents values from (0,0,0) to (1, 1, 1) and (u, v, w)
					                                                     // is the fractional part

					Accum +=
						((1 - uu) * (1 - i) + uu * i) *
						((1 - vv) * (1 - j) + vv * j) *
						((1 - ww) * (1 - k) + ww * k) *
						glm::dot(lerp[i * size * size + j * size + k], Weight);
				}
			}
		}

		return Accum;
	}

private:
	static constexpr int TileWidth = 256;
	glm::dvec3 RandomDoubles[TileWidth];
	int PermuteX[TileWidth];
	int PermuteY[TileWidth];
	int PermuteZ[TileWidth];
};