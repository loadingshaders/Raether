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

	#define SCENE4
	
	#ifdef SCENE1
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
		scene.addSpheres(Sphere(glm::vec3(0.f, -101.f, 0.f), 100.f, diffuseYeollow));
		scene.addSpheres(Sphere(glm::vec3(0.f, 0.f, 0.f), 1.f, diffuseBlue));
		scene.addSpheres(Sphere(glm::vec3(2.01f, 0.0f, 0.0f), 1.f, metalGold));
		scene.addSpheres(Sphere(glm::vec3(-2.01f, 0.0f, 0.0f), 1.f, dielectricGlass));
		scene.addSpheres(Sphere(glm::vec3(-2.01f, 0.0f, 0.0f), 0.65f, dielectricBubble));

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
		scene.addSpheres(Sphere(glm::vec3(0.f, -101.f, 0.f), 100.f, diffuseYeollow));
		scene.addSpheres(Sphere(glm::vec3(0.f, 0.f, 0.f), 1.f, diffuseBlue));
		scene.addSpheres(Sphere(glm::vec3(2.01f, 0.0f, 0.0f), 1.f, metalGold));
		scene.addSpheres(Sphere(glm::vec3(-2.01f, 0.0f, 0.0f), 1.f, dielectricGlass));
		scene.addSpheres(Sphere(glm::vec3(-2.01f, 0.0f, 0.0f), 0.65f, dielectricBubble));

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
		scene.addSpheres(Sphere(glm::vec3(0.f, -10000.f, 0.f), 10000.f, diffuseWhite));
		scene.addSpheres(Sphere(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.addSpheres(Sphere(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.addSpheres(Sphere(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.addSpheres(Sphere(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -23; a < 23; a++) {
			for (int b = -23; b < 23; b++) {
				
				float chooseMat = Utils::RandomFloat();
				glm::vec3 center = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());

				if (glm::distance(scene.SphereList[1].SphereOrigin, center) > 1.23f &&
					glm::distance(scene.SphereList[2].SphereOrigin, center) > 1.23f &&
					glm::distance(scene.SphereList[3].SphereOrigin, center) > 1.23f &&
					glm::distance(           lastOrigin           , center) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.addSpheres(Sphere(center, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.addSpheres(Sphere(center, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.addSpheres(Sphere(center, 0.2f, sphereMat));
					}
				}

				lastOrigin = center;
			}
		}

		// Camera setup
		camera.SetFocus(50.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(35.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#elif defined(SCENE4)
	{
		///Scene-3
		// Configure Materials
		std::shared_ptr<Material> diffuseWhite = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		std::shared_ptr<Material> diffuseRed = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
		std::shared_ptr<Material> dielectricGlass = std::make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> dielectricBubble = std::make_shared<Dielectric>(1.0003f / 1.5f);
		std::shared_ptr<Material> metalSteel = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);

		// Configure Spheres
		scene.addSpheres(Sphere(glm::vec3(0.f, -10000.f, 0.f), 10000.f, diffuseWhite));
		scene.addSpheres(Sphere(glm::vec3(-4.f, 1.f, 0.f), 1.f, diffuseRed));
		scene.addSpheres(Sphere(glm::vec3(0.f, 1.f, 0.f), 1.f, dielectricGlass));
		scene.addSpheres(Sphere(glm::vec3(4.f, 1.f, 0.f), 1.f, metalSteel));
		scene.addSpheres(Sphere(glm::vec3(0.f, 1.f, 0.f), 0.6f, dielectricBubble));

		static glm::vec3 lastOrigin;

		for (int a = -18; a < 18; a++) {
			for (int b = -18; b < 18; b++) {

				float chooseMat = Utils::RandomFloat();
				glm::vec3 center1 = glm::vec3(a + Utils::RandomFloat(), 0.2f, b + Utils::RandomFloat());
				glm::vec3 center2 = center1 + glm::vec3(0.f, Utils::RandomFloatInRange(0.f, 0.5f), 0.f);

				if (glm::distance(scene.SphereList[1].SphereOrigin, center1) > 1.23f &&
					glm::distance(scene.SphereList[2].SphereOrigin, center1) > 1.23f &&
					glm::distance(scene.SphereList[3].SphereOrigin, center1) > 1.23f &&
					glm::distance(lastOrigin, center1) > 0.45f) {

					std::shared_ptr<Material> sphereMat;

					if (chooseMat < 0.6f) {
						// Diffuse Spheres
						sphereMat = std::make_shared<Lambertian>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)));
						scene.addSpheres(Sphere(center1, center2, 0.2f, sphereMat));
					}
					else if (chooseMat < 0.85f) {
						// Metal Spheres
						sphereMat = std::make_shared<Metal>(glm::vec3((float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f), (float)Utils::RandomFloatInRange(0.0f, 0.99f)), (float)Utils::RandomFloatInRange(0.f, 0.5f));
						scene.addSpheres(Sphere(center1, center2, 0.2f, sphereMat));
					}
					else {
						// Glass Spheres
						sphereMat = std::make_shared<Dielectric>(1.52f);
						scene.addSpheres(Sphere(center1, center2, 0.2f, sphereMat));
					}
				}

				lastOrigin = center1;
			}
		}

		// Camera setup
		camera.SetFocus(50.f, 12.f);
		camera.SetViewPortWidth(width);
		camera.SetViewPortHeight(height);
		camera.SetPosition(glm::vec3(14.0218f, 2.0866f, 3.9276f)); //glm::vec3(0.f, 0.f, 8.f)
		camera.SetForwardDirection(glm::vec3(-0.869436f, -0.0900598f, -0.228215f)); // glm::vec3(0.0f, 0.0f, -1.0f)
		camera.SetProjection(35.f); // 45.f
		camera.SetView();
		camera.CalculateRayDirections();
	}
	#endif

	// Scene render specs
	scene.setSampleCount(10000);
	scene.setSampleBounces(100);
}

void App::updateScene() {
	renderer.Init(rae, scene, camera);

	// Main event loop
	while (rae.windowState == RaeState::ACTIVE) {

		/// Start the render
		rae.raeRenderBegin();

		/// Check for input
		if (rae.raeInputEvents()) {
			camera.HandleInput(rae);
			renderer.ResetFrameIdx();
		}

		/// Render the scene
		renderer.Render(scene, camera);

		/// End the render
		rae.raeRenderEnd();
	}

	rae.raeQuit();
}

void App::run() {
	setUpScene();
	updateScene();
}