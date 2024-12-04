#include "Application.h"

App::App() : title("Raether"),
width(800), // 800
height(800), // 800
rae(),
scene(),
camera(),
renderer()
{} // 900,500

App::~App() {}

void App::setWindow() {
	rae.raeCreateWindow(title, width, height);
}

void App::setUpScene() {
	// Window Setup
	setWindow();

	#if defined(SCENE1)
	{
		///Scene-1

		// Configure Materials
		std::shared_ptr<Material> diffuseYeollow = std::make_shared<Lambertian>(glm::dvec3(0.8, 0.8, 0.0));
		std::shared_ptr<Material> diffuseBlue = std::make_shared<Lambertian>(glm::dvec3(0.1, 0.2, 0.5));
		std::shared_ptr<Material> metalGold = std::make_shared<Metal>(glm::dvec3(1.0, 0.782, 0.344), 0.0);
		std::shared_ptr<Material> metalSilver = std::make_shared<Metal>(glm::dvec3(0.972, 0.960, 0.915), 0.3);
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.52);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.52);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -101.0, 0.0), 100.0, diffuseYeollow));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 0.0, 0.0), 1.0, diffuseBlue));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(2.01, 0.0, 0.0), 1.0, metalGold));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-2.01, 0.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-2.01, 0.0, 0.00), 0.65, dielectricBubble));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(100.0, 8.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 8.0));
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0));
		camera.SetProjection(45.0);
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE2)
	{
		///Scene-2

		// Configure Materials
		std::shared_ptr<Material> diffuseYeollow = std::make_shared<Lambertian>(glm::dvec3(0.8, 0.8, 0.0));
		std::shared_ptr<Material> diffuseBlue = std::make_shared<Lambertian>(glm::dvec3(0.1, 0.2, 0.5));
		std::shared_ptr<Material> metalGold = std::make_shared<Metal>(glm::dvec3(1.0, 0.782, 0.344), 0.0);
		std::shared_ptr<Material> metalSilver = std::make_shared<Metal>(glm::dvec3(0.972, 0.960, 0.915), 0.3);
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.52);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.52);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -101.0, 0.0), 100.0, diffuseYeollow));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 0.0, 0.0), 1.0, diffuseBlue));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(2.01, 0.0, 0.0), 1.0, metalGold));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-2.01, 0.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-2.01, 0.0, 0.0), 0.65, dielectricBubble));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.0, 62.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(-34.93, 35.6765, 36.7877)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.562163, -0.577032, -0.592458)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(4.5); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE3)
	{
		///Scene-3

		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::dvec3(0.5, 0.5, 0.5));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::dvec3(0.4, 0.2, 0.1));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.5);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, diffuseWhite));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-4.0, 1.0, 0.0), 1.0, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.0, 0.0), 1.0, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 0.6, dielectricBubble));

		static glm::dvec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				double chooseMat = Utils::RandomDouble();
				glm::dvec3 center = glm::dvec3(a + Utils::RandomDouble(), 0.2, b + Utils::RandomDouble());

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center) > 1.23 &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center) > 1.23 &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center) > 1.23 &&
					glm::distance(lastOrigin, center) > 0.45) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)));
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
					else if (chooseMat < 0.85) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)), Utils::RandomDoubleInRange(0.0, 0.5));
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52);
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
				}

				lastOrigin = center;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE4)
	{
		///Scene-4

		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::dvec3(0.5, 0.5, 0.5));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::dvec3(0.4, 0.2, 0.1));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.5);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, diffuseWhite));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-4.0, 1.0, 0.0), 1.0, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.0, 0.0), 1.0, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 0.6, dielectricBubble));

		static glm::dvec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				double chooseMat = Utils::RandomDouble();
				glm::dvec3 center1 = glm::dvec3(a + Utils::RandomDouble(), 0.2, b + Utils::RandomDouble());
				glm::dvec3 center2 = center1 + glm::dvec3(0.0, Utils::RandomDoubleInRange(0.0, 0.5), 0.0);

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(lastOrigin, center1) > 0.45) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
					else if (chooseMat < 0.85) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)), Utils::RandomDoubleInRange(0.0, 0.5));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52);
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
				}

				lastOrigin = center1;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(50.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE5)
	{
		///Scene-5

		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::dvec3(0.5, 0.5, 0.5));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::dvec3(0.4, 0.2, 0.1));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.5);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32, glm::dvec3(0.2, 0.3, 0.1), glm::dvec3(0.9));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-4.0, 1.0, 0.0), 1.0, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.0, 0.0), 1.0, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 0.6, dielectricBubble));

		static glm::dvec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				double chooseMat = Utils::RandomDouble();
				glm::dvec3 center = glm::dvec3(a + Utils::RandomDouble(), 0.2, b + Utils::RandomDouble());

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center) > 1.23 &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center) > 1.23 &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center) > 1.23 &&
					glm::distance(lastOrigin, center) > 0.45) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)));
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)), Utils::RandomDoubleInRange(0.0, 0.5));
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52);
						scene.Add(std::make_shared<Sphere>(center, 0.2, sphereMat));
					}
				}

				lastOrigin = center;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE6)
	{
		///Scene-6

		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::dvec3(0.5, 0.5, 0.5));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::dvec3(0.4, 0.2, 0.1));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.5);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32, glm::dvec3(0.2, 0.3, 0.1), glm::dvec3(0.9));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(-4.0, 1.0, 0.0), 1.0, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 1.0, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.0, 0.0), 1.0, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 1.0, 0.0), 0.6, dielectricBubble));

		static glm::dvec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				double chooseMat = Utils::RandomDouble();
				glm::dvec3 center1 = glm::dvec3(a + Utils::RandomDouble(), 0.2, b + Utils::RandomDouble());
				glm::dvec3 center2 = center1 + glm::dvec3(0.0, Utils::RandomDoubleInRange(0.0, 0.50), 0.0);

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center1) > 1.23 &&
					glm::distance(lastOrigin, center1) > 0.45) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
					else if (chooseMat < 0.85) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::dvec3(Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99), Utils::RandomDoubleInRange(0.0, 0.99)), Utils::RandomDoubleInRange(0.0, 0.5));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52);
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2, sphereMat));
					}
				}

				lastOrigin = center1;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866f, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE7)
	{
		///Scene-7

		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::dvec3(0.5));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::dvec3(0.4, 0.2, 0.1));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003 / 1.5);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32, glm::dvec3(0.2, 0.3, 0.1), glm::dvec3(0.9));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 10.0, 0.0), 10.0, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, -10.0, 0.0), 10.0, std::make_shared<Lambertian>(checkerTexture)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(18.8951, 1.88632, 3.44855)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.873826, -0.0900598, -0.210782)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE8)
	{
		///Scene-8

		// Configure Materials
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32, glm::dvec3(0.3), glm::dvec3(0.9));
		std::shared_ptr<ImageTexture> checkerImageTexture = std::make_shared<ImageTexture>("Checker/UVChecker_4K.png");

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.01, 0.0), 1.0, std::make_shared<Lambertian>(checkerImageTexture)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE9)
	{
		///Scene-9

		// Configure Materials
		std::shared_ptr<NoiseTexture> perlinNoise = std::make_shared<NoiseTexture>(0.2);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, std::make_shared<Lambertian>(perlinNoise)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.01, 0.0), 1.0, std::make_shared<Lambertian>(perlinNoise)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(14.0218, 2.0866, 3.9276)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(-0.869436, -0.0900598, -0.228215)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE10)
	{
		///Scene-10

		// Configure Materials
		auto leftRed = std::make_shared<Lambertian>(glm::dvec3(1.0, 0.2, 0.2));
		auto backGreen = std::make_shared<Lambertian>(glm::dvec3(0.2, 1.0, 0.2));
		auto rightBlue = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.2, 1.0));
		auto upperOrange = std::make_shared<Lambertian>(glm::dvec3(1.0, 0.5, 0.0));
		auto lowerTeal = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.8, 0.8));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -1.5, -5.0), glm::dvec3(0.0, 0.0, 3.0), glm::dvec3(0.0, 3.0, 0.0), leftRed));
		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.5, -1.5, -5.5), glm::dvec3(3.0, 0.0, 0.0), glm::dvec3(0.0, 3.0, 0.0), backGreen));
		scene.Add(std::make_shared<Quad>(glm::dvec3(2.0, -1.5, -5.0), glm::dvec3(0.0, 0.0, 3.0), glm::dvec3(0.0, 3.0, 0.0), rightBlue));
		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.5, 2.0, -5.0), glm::dvec3(3.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 3.0), upperOrange));
		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.5, -2.0, -5.0), glm::dvec3(3.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 3.0), lowerTeal));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 8.0)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE11)
	{
		///Scene-11

		// Configure Materials
		std::shared_ptr<NoiseTexture> tiledNoise = std::make_shared<NoiseTexture>(0.32);
		std::shared_ptr<DiffuseLight> diffusedLight = std::make_shared<DiffuseLight>(glm::dvec3(5.0));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(3.28, 0.2, 2.3), glm::dvec3(1.5, 0.0, 0.0), glm::dvec3(0.0, 1.5, 0.0), diffusedLight));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, -10000.0, 0.0), 10000.0, std::make_shared<Lambertian>(tiledNoise)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 1.01, 0.0), 1.0, std::make_shared<Lambertian>(tiledNoise)));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(4.0, 3.2, 0.0), 0.65, diffusedLight));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.0, 0.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(-6.89692, 1.89061, -1.04361)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.895924, -0.0334501, 0.110963)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE12)
	{
		///Scene-12

		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::dvec3(10.0));
		auto diffusedRed = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(2.0f, -2.0f, -4.0f), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 4.0, 0.0), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, 2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.0, 1.99, -3.0), glm::dvec3(2.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 2.0), diffusedHighLight)); // Light Quad

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 9.7);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 7.7)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE13)
	{
		///Scene-13

		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::dvec3(10.0));
		auto diffusedRed = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 4.0, 0.0), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, 2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.0, 1.99, -3.0), glm::dvec3(2.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 2.0), diffusedHighLight)); // Light Quad

		// Configure Instances
		//scene.Add(Box3D(glm::dvec3(-1.14, -2.0, -2.2), glm::dvec3(0.06, 0.4, -3.4), diffusedWhite));
		//scene.Add(Box3D(glm::dvec3(-0.06, -2.0, -0.6), glm::dvec3(1.14, -0.8, -1.8), diffusedWhite));

		scene.Add(std::make_shared<Box>(glm::dvec3(-1.14, -2.0, -2.2), glm::dvec3(0.06, 0.4, -3.4), diffusedWhite));
		scene.Add(std::make_shared<Box>(glm::dvec3(-0.06, -2.0, -0.6), glm::dvec3(1.14, -0.8, -1.8), diffusedWhite));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 9.7);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 7.7)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE14)
	{
		///Scene-14

		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::dvec3(9.00));
		auto diffusedRed = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 4.0, 0.0), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, 2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.0, 1.99, -3.0), glm::dvec3(2.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 2.0), diffusedHighLight)); // Light Quad

		// Configure Instances
		std::shared_ptr<Hittable> box1 = std::make_shared<Box>(glm::dvec3(-1.14, -2.0, -2.2), glm::dvec3(0.06, 0.4, -3.4), diffusedWhite);
		box1 = std::make_shared<Translate>(box1, glm::dvec3(0.72, -0.4, 0.0));
		box1 = std::make_shared<RotateX>(box1, 15.0);
		box1 = std::make_shared<RotateY>(box1, 18.0);
		scene.Add(box1);

		std::shared_ptr<Hittable> box2 = std::make_shared<Box>(glm::dvec3(-0.06, -2.0, -0.6), glm::dvec3(1.14, -0.8, -1.8), diffusedWhite);
		box2 = std::make_shared<Translate>(box2, glm::dvec3(-0.22, 0.0, 0.0));
		box2 = std::make_shared<RotateY>(box2, -18.0);
		box2 = std::make_shared<RotateZ>(box2, 7.0);
		scene.Add(box2);

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 9.7);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 7.7)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE15)
	{
		///Scene-15

		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::dvec3(9.0));
		auto diffusedRed = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(2.0, -2.0, -4.0), glm::dvec3(0.0, 0.0, 4.0), glm::dvec3(0.0, 4.0, 0.0), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 4.0, 0.0), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, -2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::dvec3(-2.0, 2.0, -4.0), glm::dvec3(4.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 4.0), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::dvec3(-1.0, 1.99, -3.0), glm::dvec3(2.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 2.0), diffusedHighLight)); // Light Quad

		// Configure Instances
		std::shared_ptr<Hittable> box1 = std::make_shared<Box>(glm::dvec3(-1.14, -2.0, -2.2), glm::dvec3(0.06, 0.4, -3.4), diffusedWhite);
		box1 = std::make_shared<Translate>(box1, glm::dvec3(0.72, -0.4, 0.0));
		box1 = std::make_shared<RotateX>(box1, 15.0);
		box1 = std::make_shared<RotateY>(box1, 18.0);

		std::shared_ptr<Hittable> box2 = std::make_shared<Box>(glm::dvec3(-0.06, -2.0, -0.6), glm::dvec3(1.14, -0.8, -1.8), diffusedWhite);
		box2 = std::make_shared<Translate>(box2, glm::dvec3(-0.22, 0.0, 0.0));
		box2 = std::make_shared<RotateY>(box2, -18.0);
		box2 = std::make_shared<RotateZ>(box2, 7.0);

		scene.Add(std::make_shared<Volume>(box1, 1.8, glm::dvec3(0.0)));
		scene.Add(std::make_shared<Volume>(box2, 1.8, glm::dvec3(1.0)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 9.7);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 7.7)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE16)
	{
		///Scene-16

		// Configure Materials
		auto diffusedLight = std::make_shared<DiffuseLight>(glm::dvec3(8.0));
		auto diffusedBlack = std::make_shared<Lambertian>(glm::dvec3(0.0));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.48, 0.83, 0.53));
		auto diffusedBurntOrange = std::make_shared<Lambertian>(glm::dvec3(0.7, 0.3, 0.1));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73));
		auto diffusedBlue = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.4, 0.9));
		auto dielectricGlass = std::make_shared<Dielectric>(1.5);
		auto brushedAluminum = std::make_shared<Metal>(glm::dvec3(0.8, 0.8, 0.9), 1.0);
		auto earthTopoMap = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("Earthmap/EarthTopoMap.png"));
		auto perlinNoise = std::make_shared<Lambertian>(std::make_shared<NoiseTexture>(5.0));

		// Configure Boxes
		auto box1 = std::make_shared<HittableList>();

		int boxesPerSide = 50;
		double boxWidth = 100.0;
		double axisOffset = (boxesPerSide * boxWidth) / 2.0;

		for (int i = 0; i < boxesPerSide; i++) {
			for (int j = 0; j < boxesPerSide; j++) {

				double x0 = -axisOffset + i * boxWidth;
				double y0 = 0.0;
				double z0 = -axisOffset + j * boxWidth;
				double x1 = x0 + boxWidth - 0.1;
				double y1 = Utils::RandomDoubleInRange(0.01 * boxWidth, boxWidth - (0.01 * boxWidth));
				double z1 = z0 + boxWidth - 0.1;

				box1->Add(std::make_shared<Box>(glm::dvec3(x0, y0, z0), glm::dvec3(x1, y1, z1), diffusedGreen));
			}
		}

		// Build box1 BVH
		box1->BuildBVH();
		scene.Add(box1);

		// Configure Quads
		scene.Add(std::make_shared<Quad>(glm::dvec3(123.0, 554.01, 147.0), glm::dvec3(300.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 265.0), diffusedBlack));
		scene.Add(std::make_shared<Quad>(glm::dvec3(123.0, 554.0, 147.0), glm::dvec3(300.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 265.0), diffusedLight)); // Light Quad

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(400.0, 400.0, 200.0), glm::dvec3(430.0, 400.0, 200.0), 50.0, diffusedBurntOrange));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 150.0, 145.0), 50.0, brushedAluminum));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(260.0, 150.0, 45.0), 50.0, dielectricGlass));

		auto boundary = std::make_shared<Sphere>(glm::dvec3(360.0, 150.0, 145.0), 69.95, dielectricGlass);
		scene.Add(std::make_shared<Volume>(boundary, 0.2, glm::dvec3(0.2, 0.4, 0.9)));
		boundary = std::make_shared<Sphere>(glm::dvec3(360.0, 150.0, 145.0), 70.0, dielectricGlass);
		scene.Add(boundary);

		boundary = std::make_shared<Sphere>(glm::dvec3(0.0), 5000.0, dielectricGlass);
		scene.Add(std::make_shared<Volume>(boundary, 0.00008, glm::dvec3(1.0)));

		scene.Add(std::make_shared<Sphere>(glm::dvec3(400.0, 200.0, 400.0), 100.0, earthTopoMap));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(220.0, 280.0, 300.0), 80.0, perlinNoise));

		// Configure Boxes of Spheres
		auto box2 = std::make_shared<HittableList>();

		int sphereCount = 1000;
		for (int i = 0; i < sphereCount; i++) {
			box2->Add(std::make_shared<Sphere>(Utils::RandomOffset2(0.0, 165.0), 10.0, diffusedWhite));
		}

		// Build box2 BVH
		box2->BuildBVH();
		scene.Add(std::make_shared<Translate>(std::make_shared<RotateY>(box2, 15.0), glm::dvec3(-100.0, 270.0, 395.0)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the Entire Scene BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.0, 0.0);
		camera.SetCamMovement(0.01, 60.0);
		camera.SetJitterStrength(0.002);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(470.0, 278.0, -600.0)); // glm::dvec3(555.928, 257.911, -691.695)
		camera.SetForwardDirection(glm::dvec3(-0.29, 0.01, 0.95)); // glm::dvec3(-0.342436, 0.0428016, 0.938567)
		camera.SetProjection(40.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE17)
	{
		///Scene-17

		// Configure Materials
		auto diffusedLight = std::make_shared<DiffuseLight>(glm::dvec3(10.0, 9.8, 9.85));
		auto diffusedBlack = std::make_shared<Lambertian>(glm::dvec3(0.0));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::dvec3(0.48, 0.83, 0.53));
		auto diffusedBurntOrange = std::make_shared<Lambertian>(glm::dvec3(0.7, 0.3, 0.1));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::dvec3(0.73));
		auto diffusedBlue = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.4, 0.9));
		auto dielectricGlass = std::make_shared<Dielectric>(1.5);
		auto brushedAluminum = std::make_shared<Metal>(glm::dvec3(0.8, 0.8, 0.9), 1.0);
		auto earthTopoMap = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("Earthmap/EarthTopoMap.png"));
		auto perlinNoise = std::make_shared<Lambertian>(std::make_shared<NoiseTexture>(5.0));

		// Configure Boxes
		auto box1 = std::make_shared<HittableList>();

		int boxesPerSide = 50;
		double boxWidth = 100.0;
		double axisOffset = (boxesPerSide * boxWidth) / 2.0;

		for (int i = 0; i < boxesPerSide; i++) {
			for (int j = 0; j < boxesPerSide; j++) {

				double x0 = -axisOffset + i * boxWidth;
				double y0 = 0.0;
				double z0 = -axisOffset + j * boxWidth;
				double x1 = x0 + boxWidth - 0.1;
				double y1 = Utils::RandomDoubleInRange(0.01 * boxWidth, boxWidth - (0.01 * boxWidth));
				double z1 = z0 + boxWidth - 0.1;

				box1->Add(std::make_shared<Box>(glm::dvec3(x0, y0, z0), glm::dvec3(x1, y1, z1), diffusedGreen));
			}
		}

		// Build box1 BVH
		box1->BuildBVH();
		scene.Add(box1);

		// Configure Quads
		scene.Add(std::make_shared<Quad>(glm::dvec3(123.0, 554.02, 147.0), glm::dvec3(300.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 265.0), diffusedBlack));
		scene.Add(std::make_shared<Quad>(glm::dvec3(123.0, 554.0, 147.0), glm::dvec3(300.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 265.0), diffusedLight)); // Light Quad

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::dvec3(400.0, 400.0, 200.0), glm::dvec3(430.0, 400.0, 200.0), 50.0, diffusedBurntOrange));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(0.0, 150.0, 145.0), 50.0, brushedAluminum));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(260.0, 150.0, 45.0), 50.0, dielectricGlass));

		auto boundary = std::make_shared<Sphere>(glm::dvec3(360.0, 150.0, 145.0), 69.95, dielectricGlass);
		scene.Add(std::make_shared<Volume>(boundary, 0.2, glm::dvec3(0.2, 0.4, 0.9)));
		boundary = std::make_shared<Sphere>(glm::dvec3(360.0, 150.0, 145.0), 70.0, dielectricGlass);
		scene.Add(boundary);

		boundary = std::make_shared<Sphere>(glm::dvec3(0.0), 5000.0, dielectricGlass);
		scene.Add(std::make_shared<Volume>(boundary, 0.00008, glm::dvec3(1.0)));

		scene.Add(std::make_shared<Sphere>(glm::dvec3(400.0, 200.0, 400.0), 100.0, earthTopoMap));
		scene.Add(std::make_shared<Sphere>(glm::dvec3(220.0, 280.0, 300.0), 80.0, perlinNoise));

		// Configure Boxes of Spheres
		auto box2 = std::make_shared<HittableList>();

		int sphereCount = 1000;
		for (int i = 0; i < sphereCount; i++) {

			double random = Utils::RandomDouble();

			if (random < 0.45) box2->Add(std::make_shared<Sphere>(Utils::RandomOffset2(0.0, 165.0), 10.0, diffusedWhite));
			else if (random < 7.0) box2->Add(
				std::make_shared<RotateX>(
					std::make_shared<RotateY>(
						std::make_shared<RotateZ>(
							std::make_shared<Box>(
								Utils::RandomOffset2(0.0, 165.0), diffusedWhite, glm::dvec3(20.0)),
							Utils::RandomFloatInRange(1.0, 22.5)),
						Utils::RandomFloatInRange(1.0, 22.5)),
					Utils::RandomFloatInRange(1.0, 22.5)));
		}

		// Build box2 BVH
		box2->BuildBVH();
		scene.Add(std::make_shared<Translate>(std::make_shared<RotateY>(box2, 0.0), glm::dvec3(-100.0, 270.0, 395.0)));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlack, ColorBlack);

		// Build the Entire Scene BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.0, 0.0);
		camera.SetCamMovement(0.01, 60.0);
		camera.SetJitterStrength(0.002);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(470.0, 278.0, -600.0)); // glm::dvec3(555.928, 257.911, -691.695)
		camera.SetForwardDirection(glm::dvec3(-0.29, 0.01, 0.95)); // glm::dvec3(-0.342436, 0.0428016, 0.938567)
		camera.SetProjection(40.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE18)
	{
		///Scene-18

		// Configure Materials
		auto leftRed = std::make_shared<Lambertian>(glm::dvec3(1.0, 0.2, 0.2));
		auto backGreen = std::make_shared<Lambertian>(glm::dvec3(0.2, 1.0, 0.2));
		auto rightBlue = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.2, 1.0));
		auto upperOrange = std::make_shared<Lambertian>(glm::dvec3(1.0, 0.5, 0.0));
		auto lowerTeal = std::make_shared<Lambertian>(glm::dvec3(0.2, 0.8, 0.8));

		// Configure Planes
		scene.Add(std::make_shared<Triangle>(glm::dvec3(-2.0, 1.6, -1.7), glm::dvec3(-2.0, 1.6, -4.7), glm::dvec3(-2.0, -1.4, -1.7), leftRed));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(-2.0, -1.6, -5.3), glm::dvec3(-2.0, -1.6, -2.3), glm::dvec3(-2.0, 1.4, -5.3), leftRed));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(2.0, 1.6, -1.7), glm::dvec3(2.0, 1.6, -4.7), glm::dvec3(2.0, -1.4, -1.7), rightBlue));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(2.0, -1.6, -5.3), glm::dvec3(2.0, -1.6, -2.3), glm::dvec3(2.0, 1.4, -5.3), rightBlue));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(-1.6, 2.0, -5.3), glm::dvec3(1.4, 2.0, -5.3), glm::dvec3(-1.6, 2.0, -2.3), upperOrange));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(1.6, 2.0, -1.7), glm::dvec3(1.6, 2.0, -4.7), glm::dvec3(-1.4, 2.0, -1.7), upperOrange));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(-1.6, -2.0, -5.3), glm::dvec3(1.4, -2.0, -5.3), glm::dvec3(-1.6, -2.0, -2.3), lowerTeal));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(1.6, -2.0, -1.7), glm::dvec3(1.6, -2.0, -4.7), glm::dvec3(-1.4, -2.0, -1.7), lowerTeal));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(-1.65, -1.65, -5.5), glm::dvec3(1.35, -1.65, -5.5), glm::dvec3(-1.65, 1.35, -5.5), backGreen));
		scene.Add(std::make_shared<Triangle>(glm::dvec3(1.65, 1.65, -5.5), glm::dvec3(1.65, -1.35, -5.5), glm::dvec3(-1.35, 1.65, -5.5), backGreen));

		// Set Background Color
		scene.SetBackgroundColor(ColorBlue, ColorWhite);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.0, 12.0);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::dvec3(0.0, 0.0, 8.0)); // glm::dvec3(0.0, 0.0, 8.0)
		camera.SetForwardDirection(glm::dvec3(0.0, 0.0, -1.0)); // glm::dvec3(0.0, 0.0, -1.0)
		camera.SetProjection(30.0); // 45.0
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#endif

	// Scene Render Specs
	scene.SetSampleCount(100000);
	scene.SetSampleBounces(1000);
}

void App::updateScene() {
	renderer.Init(rae, scene, camera);

	/// Main event loop
	while (rae.windowState == RaeState::ACTIVE) {

		/// Start the render
		rae.raeRenderBegin();

		/// Check for input
		if (rae.raeInputEvents()) {
			camera.HandleInput(rae);
			renderer.ResetFrameIdx();
		}

		/// Catch the start time
		start = logtime;

		/// Render the scene
		renderer.Render(scene, camera);

		/// Catch the end time
		end = logtime;

		totalTime += elapsed(end - start).count();
		frameCount++;

		if (PrintPerFrameTime) {
			printf("_____________________________________________________\n\n"
				"       Last Frame Rendere Time    |  %" PRId64 "              \n"
				"       Avg Frame Rendere Time     |  %f              \n"
				"       Avg Frame Per Second       |  %f              \n"
				"" "_____________________________________________________\n\n", elapsed(end - start).count(), totalTime / frameCount, (1.0 / elapsed(end - start).count()) * 1000.f);
		}

		/// End the render
		rae.raeRenderEnd();
	}

	if (PrintFinalRenderTime) {
		printf("_________________________________________________________________\n\n"
			"\033[0;32m" "        Total Objects Drawn           " "\033[0m" "| " "\033[0;32m" "%-10" PRIu64 " \n"
			"\033[0;32m" "        Total Frames Rendered         " "\033[0m" "| " "\033[0;32m" "%-10d " " \n"
			"\033[0;33m" "        Avg Frame Render Time         " "\033[0m" "| " "\033[0;33m" "%-10.5f " "  ms\n"
			"\033[0;33m" "        Avg Frame Per Second          " "\033[0m" "| " "\033[0;33m" "%-10.5f " " fps\n"
			"\033[0m"
			"_________________________________________________________________\n\n",
			scene.GetObjectList().size(), frameCount, totalTime / frameCount, (1.0 / (totalTime / frameCount)) * 1000.f);
	}

	/// Clear the Scene Buffer
	scene.Clear();

	/// Quit the Backend
	rae.raeQuit();
}

void App::run() {
	setUpScene();
	updateScene();
}