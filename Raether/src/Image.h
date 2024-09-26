#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class Image {
public:
	Image();
	Image(const char* imageFilename);
	~Image();

	const int GetWidth() const;
	const int GetHeight() const;

	bool Load(std::string& imageFilePath);
	unsigned char* PixelData(int x, int y) const;

private:
	void ConvertToRGB();
	unsigned char FloatToRGB(float value) const;
	int Clamp(int value, int min, int max) const;

private:
	int BytesPerPixel = 3;
	float* FloatImagePtr;
	unsigned char* RGBImagePtr;
	uint64_t BytesPerScanline;
	int ImageWidth, ImageHeight;
};