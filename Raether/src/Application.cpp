#include "Application.h"

App::App() : title("Raether"),
			 width(800), // 800
			 height(800), // 800
			 rae(),
			 scene(),
			 camera(),
			 renderer()
{
}//900,500
App::~App() { }

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
		std::shared_ptr<Material> diffuseYeollow = std::make_shared<Lambertian>(glm::vec3(0.8f, 0.8f, 0.0f));
		std::shared_ptr<Material> diffuseBlue = std::make_shared<Lambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
		std::shared_ptr<Material> metalGold = std::make_shared<Metal>(glm::vec3(1.f, 0.782f, 0.344f), 0.f);
		std::shared_ptr<Material> metalSilver = std::make_shared<Metal>(glm::vec3(0.972f, 0.960f, 0.915f), 0.3f);
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.52f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.003f / 1.52f);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -101.f, 0.f), 100.f, diffuseYeollow));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 0.f, 0.f), 1.f, diffuseBlue));
		scene.Add(std::make_shared<Sphere>(glm::vec3(2.01f, 0.0f, 0.0f), 1.f, metalGold));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-2.01f, 0.0f, 0.0f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-2.01f, 0.0f, 0.0f), 0.65f, dielectricBubble));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(100.f, 8.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(0.f, 0.f, 8.f));
		camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f));
		camera.SetProjection(45.0f);
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE2)
	{
		///Scene-2
		// Configure Materials
		std::shared_ptr<Material> diffuseYeollow = std::make_shared<Lambertian>(glm::vec3(0.8f, 0.8f, 0.0f));
		std::shared_ptr<Material> diffuseBlue = std::make_shared<Lambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
		std::shared_ptr<Material> metalGold = std::make_shared<Metal>(glm::vec3(1.f, 0.782f, 0.344f), 0.f);
		std::shared_ptr<Material> metalSilver = std::make_shared<Metal>(glm::vec3(0.972f, 0.960f, 0.915f), 0.3f);
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.52f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.003f / 1.52f);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -101.f, 0.f), 100.f, diffuseYeollow));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 0.f, 0.f), 1.f, diffuseBlue));
		scene.Add(std::make_shared<Sphere>(glm::vec3(2.01f, 0.0f, 0.0f), 1.f, metalGold));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-2.01f, 0.0f, 0.0f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-2.01f, 0.0f, 0.0f), 0.65f, dielectricBubble));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.f, 62.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(-34.93f, 35.6765, 36.7877)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.562163f, -0.577032f, -0.592458f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(4.5f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE3)
	{
		///Scene-3
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, diffuseWhite));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {
				
				float chooseMat = Utils::RandomFloat();
				glm::vec3 center = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center) > 1.23f &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center) > 1.23f &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center) > 1.23f &&
					glm::distance(              lastOrigin              , center) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
				}

				lastOrigin = center;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE4)
	{
		///Scene-4
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, diffuseWhite));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				float chooseMat = Utils::RandomFloat();
				glm::vec3 center1 = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());
				glm::vec3 center2 = center1 + glm::vec3(0.f, Utils::RandomFloatInRange(0.f, 0.5f), 0.f);

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(              lastOrigin              , center1) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
				}

				lastOrigin = center1;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(50.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE5)
	{
		///Scene-5
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32f, glm::vec3(0.2f, 0.3f, 0.1f), glm::vec3(0.9f));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				float chooseMat = Utils::RandomFloat();
				glm::vec3 center = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center) > 1.23f &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center) > 1.23f &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center) > 1.23f &&
					glm::distance(lastOrigin, center) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
					}
				}

				lastOrigin = center;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE6)
	{
		///Scene-6
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32f, glm::vec3(0.2f, 0.3f, 0.1f), glm::vec3(0.9f));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -NumofProcSpheres; a < NumofProcSpheres; a++) {
			for (int b = -NumofProcSpheres; b < NumofProcSpheres; b++) {

				float chooseMat = Utils::RandomFloat();
				glm::vec3 center1 = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());
				glm::vec3 center2 = center1 + glm::vec3(0.f, Utils::RandomFloatInRange(0.f, 0.5f), 0.f);

				if (glm::distance(scene.GetObjectList()[1]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(scene.GetObjectList()[2]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(scene.GetObjectList()[3]->ObjectOrigin, center1) > 1.23f &&
					glm::distance(lastOrigin, center1) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.Add(std::make_shared<Sphere>(center1, center2, 0.2f, sphereMat));
					}
				}

				lastOrigin = center1;
			}
		}

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE7)
	{
		///Scene-7
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32f, glm::vec3(0.2f, 0.3f, 0.1f), glm::vec3(0.9f));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 10.f, 0.f), 10.f, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, -10.f, 0.f), 10.f, std::make_shared<Lambertian>(checkerTexture)));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(18.8951f, 1.88632f, 3.44855f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.873826f, -0.0900598f, -0.210782f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f);
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE8)
	{
		///Scene-8
		// Configure Materials
		std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(0.32f, glm::vec3(0.3f), glm::vec3(0.9f));
		std::shared_ptr<ImageTexture> checkerImageTexture = std::make_shared<ImageTexture>("Checker/UVChecker_4K.png");

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, std::make_shared<Lambertian>(checkerTexture)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.01f, 0.f), 1.f, std::make_shared<Lambertian>(checkerImageTexture)));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE9)
	{
		///Scene-9
		// Configure Materials
		std::shared_ptr<NoiseTexture> perlinNoise = std::make_shared<NoiseTexture>(0.2);

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, std::make_shared<Lambertian>(perlinNoise)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.01f, 0.f), 1.f, std::make_shared<Lambertian>(perlinNoise)));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE10)
	{
		///Scene-10
		// Configure Materials
		auto leftRed = std::make_shared<Lambertian>(glm::vec3(1.0f, 0.2f, 0.2f));
		auto backGreen = std::make_shared<Lambertian>(glm::vec3(0.2f, 1.0f, 0.2f));
		auto rightBlue = std::make_shared<Lambertian>(glm::vec3(0.2f, 0.2f, 1.0f));
		auto upperOrange = std::make_shared<Lambertian>(glm::vec3(1.0f, 0.5f, 0.0f));
		auto lowerTeal = std::make_shared<Lambertian>(glm::vec3(0.2f, 0.8f, 0.8f));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -1.5f, -5.0f), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 3.0f, 0.0f), leftRed));
		scene.Add(std::make_shared<Quad>(glm::vec3(-1.5f, -1.5f, -5.5f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 3.0f, 0.0f), backGreen));
		scene.Add(std::make_shared<Quad>(glm::vec3(2.0f, -1.5f, -5.0f), glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 3.0f, 0.0f), rightBlue));
		scene.Add(std::make_shared<Quad>(glm::vec3(-1.5f, 2.0f, -5.0f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 3.0f), upperOrange));
		scene.Add(std::make_shared<Quad>(glm::vec3(-1.5f, -2.0f, -5.0f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 3.0f), lowerTeal));

		// Set Background Color
		scene.SetBackgroundColor(blue, white);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(0.0f, 0.0f, 8.0f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE11)
	{
		///Scene-11
		// Configure Materials
		std::shared_ptr<NoiseTexture> tiledNoise = std::make_shared<NoiseTexture>(0.32);
		std::shared_ptr<DiffuseLight> diffusedLight = std::make_shared<DiffuseLight>(glm::vec3(5.f));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::vec3(3.28f, 0.2f, 2.3f), glm::vec3(1.5f, 0.0f, 0.0f), glm::vec3(0.0f, 1.5f, 0.0f), diffusedLight));

		// Configure Spheres
		scene.Add(std::make_shared<Sphere>(glm::vec3(0.f, -10000.f, 0.f), 10000.f, std::make_shared<Lambertian>(tiledNoise)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 1.01f, 0.f), 1.f, std::make_shared<Lambertian>(tiledNoise)));
		scene.Add(std::make_shared<Sphere>(glm::vec3(4.f, 3.2f, 0.f), 0.65f, diffusedLight));

		// Set Background Color
		scene.SetBackgroundColor(black, black);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(0.f, 0.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(-6.89692, 1.89061, -1.04361)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.895924f, -0.0334501f, 0.110963f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE12)
	{
		///Scene-12
		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::vec3(10.0f));
		auto diffusedRed = std::make_shared<Lambertian>(glm::vec3(0.65f, 0.05f, 0.05f));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::vec3(0.12f, 0.45f, 0.15f));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::vec3(0.73f, 0.73f, 0.73f));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, 2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::vec3(-1.0f, 1.99f, -3.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f), diffusedHighLight)); // Light Quad

		// Set Background Color
		scene.SetBackgroundColor(black, black);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 9.7f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(0.0f, 0.0f, 7.7f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE13)
	{
		///Scene-13
		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::vec3(10.0f));
		auto diffusedRed = std::make_shared<Lambertian>(glm::vec3(0.65f, 0.05f, 0.05f));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::vec3(0.12f, 0.45f, 0.15f));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::vec3(0.73f, 0.73f, 0.73f));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, 2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::vec3(-1.0f, 1.99f, -3.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f), diffusedHighLight)); // Light Quad

		// Configure Instances
		//scene.Add(Box3D(glm::vec3(-1.14f, -2.0f, -2.2f), glm::vec3(0.06f, 0.4f, -3.4f), diffusedWhite));
		//scene.Add(Box3D(glm::vec3(-0.06f, -2.0f, -0.6f), glm::vec3(1.14f, -0.8f, -1.8f), diffusedWhite));

		scene.Add(std::make_shared<Box>(glm::vec3(-1.14f, -2.0f, -2.2f), glm::vec3(0.06f, 0.4f, -3.4f), diffusedWhite));
		scene.Add(std::make_shared<Box>(glm::vec3(-0.06f, -2.0f, -0.6f), glm::vec3(1.14f, -0.8f, -1.8f), diffusedWhite));

		// Set Background Color
		scene.SetBackgroundColor(black, black);

		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 9.7f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(0.0f, 0.0f, 7.7f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE14)
	{
		///Scene-14
		// Configure Materials
		auto diffusedHighLight = std::make_shared<DiffuseLight>(glm::vec3(9.0f));
		auto diffusedRed = std::make_shared<Lambertian>(glm::vec3(0.65f, 0.05f, 0.05f));
		auto diffusedGreen = std::make_shared<Lambertian>(glm::vec3(0.12f, 0.45f, 0.15f));
		auto diffusedWhite = std::make_shared<Lambertian>(glm::vec3(0.73f, 0.73f, 0.73f));

		// Configure Planes
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedRed)); // Left Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(2.0f, -2.0f, -4.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedGreen)); // Right Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 4.0f, 0.0f), diffusedWhite)); // Back Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, -2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Bottom Quad
		scene.Add(std::make_shared<Quad>(glm::vec3(-2.0f, 2.0f, -4.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 4.0f), diffusedWhite)); // Upper Quad

		scene.Add(std::make_shared<Quad>(glm::vec3(-1.0f, 1.99f, -3.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f), diffusedHighLight)); // Light Quad

		// Configure Instances
		std::shared_ptr<Hittable> box1 = std::make_shared<Box>(glm::vec3(-1.14f, -2.0f, -2.2f), glm::vec3(0.06f, 0.4f, -3.4f), diffusedWhite);
		box1 = std::make_shared<Translate>(box1, glm::vec3(0.72f, -0.4f, 0.0f));
		box1 = std::make_shared<RotateX>(box1, 15.0f);
		box1 = std::make_shared<RotateY>(box1, 18.0f);
		scene.Add(box1);

		std::shared_ptr<Hittable> box2 = std::make_shared<Box>(glm::vec3(-0.06f, -2.0f, -0.6f), glm::vec3(1.14f, -0.8f, -1.8f), diffusedWhite);
		box2 = std::make_shared<Translate>(box2, glm::vec3(-0.22f, 0.0f, 0.0f));
		box2 = std::make_shared<RotateY>(box2, -18.0f);
		box2 = std::make_shared<RotateZ>(box2, 7.0f);
		scene.Add(box2);

		// Set Background Color
		scene.SetBackgroundColor(black, black);
		
		// Build the BVH
		scene.BuildBVH();

		// Camera setup
		camera.SetFocus(10.f, 9.7f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(0.0f, 0.0f, 7.7f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(30.f); // 45.f
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