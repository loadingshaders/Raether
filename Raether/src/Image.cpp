#include "Image.h"

#ifdef _MSC_VER
#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb\stb_image.h"

Image::Image() :
	BytesPerPixel(3),
	FloatImagePtr(nullptr),
	RGBImagePtr(nullptr),
	BytesPerScanline(0),
	ImageWidth(0),
	ImageHeight(0)
{}

Image::Image(const char* imageFilename) :
	BytesPerPixel(3),
	FloatImagePtr(nullptr),
	RGBImagePtr(nullptr),
	BytesPerScanline(0),
	ImageWidth(0),
	ImageHeight(0)
{
	std::string Filename(imageFilename);

	if (Load("assets/textures/" + Filename)) return;
	if (Load("../assets/textures/" + Filename)) return;
	if (Load("../../assets/textures/" + Filename)) return;
	if (Load("../../../assets/textures/" + Filename)) return;
	if (Load("../../../../assets/textures/" + Filename)) return;
	if (Load("../../../../../assets/textures/" + Filename)) return;
	if (Load("../../../../../../assets/textures/" + Filename)) return;
	if (Load("../../../../../../../assets/textures/" + Filename)) return;
	if (Load("../../../../../../../../assets/textures/" + Filename)) return;
	if (Load("../../../../../../../../../assets/textures/" + Filename)) return;

	std::cerr << "Could not load image file '" << Filename << "'\n";
}

Image::~Image() {
	delete[] RGBImagePtr;
	STBI_FREE(FloatImagePtr);
}

const int Image::GetWidth() const {
	return (FloatImagePtr == nullptr) ? 0 : ImageWidth;
}

const int Image::GetHeight() const {
	return (FloatImagePtr == nullptr) ? 0 : ImageHeight;
}

bool Image::Load(std::string& imageFilePath) {

	int n = BytesPerPixel;
	FloatImagePtr = stbi_loadf(imageFilePath.c_str(), &ImageWidth, &ImageHeight, &n, BytesPerPixel);

	if (FloatImagePtr == nullptr) return false;

	BytesPerScanline = ImageWidth * BytesPerPixel;
	// Convert the Image Data from [0-1] space to [0-255] space
	ConvertToRGB();

	return true;
}

unsigned char* Image::PixelData(int x, int y) const {

	if (RGBImagePtr == nullptr) {
		static unsigned char Magenta[] = { 255, 0, 255 };
		return Magenta;
	}

	x = Clamp(x, 0, ImageWidth - 1);
	y = Clamp(y, 0, ImageHeight - 1);

	return (RGBImagePtr + x * BytesPerPixel + y * BytesPerScanline);
}

void Image::ConvertToRGB() {

	uint64_t totalBytes = ImageWidth * ImageHeight * BytesPerPixel;
	RGBImagePtr = new unsigned char[totalBytes];

	float* FData = FloatImagePtr;
	unsigned char* RGBData = RGBImagePtr;

	/// For a 2x2 image the stbi_Loadf would return, the [(Float-1)1st Pixel's Red channel] -> Pointer
	// (Float-1)1st Pixel's R,  (Float-2)1st Pixel's G,  (Float-3)1st Pixel's B
	// (Float-4)2nd Pixel's R,  (Float-5)2nd Pixel's G,  (Float-6)2nd Pixel's B
	// (Float-7)3rd Pixel's R,  (Float-8)3rd Pixel's G,  (Float-9)3rd Pixel's B
	// (Float-10)4th Pixel's R, (Float-11)4th Pixel's G, (Float-12)4th Pixel's B
	for (int i = 0; i < totalBytes; i++, FData++, RGBData++) {
		*RGBData = FloatToRGB(*FData);
	}
}

unsigned char Image::FloatToRGB(float value) const {
	if (value <= 0.f) {
		return 0;
	}
	else if (value >= 1.f) {
		return 255;
	}
	return static_cast<unsigned char>(256.f * value);
}

int Image::Clamp(int value, int min, int max) const {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	return value;
}

#ifdef _MSC_VER
#pragma warning (pop)
#endif