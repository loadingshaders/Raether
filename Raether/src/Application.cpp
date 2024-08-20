#include "Application.h"

App::App() : title("Raether"),
			 width(800),
			 height(800),
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

	// Configure Materials
	{
		std::shared_ptr<Material> diffuseYeollow = std::make_shared<Lambertian>(glm::vec3(0.8f, 0.8f, 0.0f));
		std::shared_ptr<Material> diffuseBlue = std::make_shared<Lambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
		std::shared_ptr<Material> metalGold = std::make_shared<Metal>(glm::vec3(1.f, 0.782f, 0.344f), 1.f);
		std::shared_ptr<Material> metalSilver = std::make_shared<Metal>(glm::vec3(0.972f, 0.960f, 0.915f), 0.3f);
		scene.addMaterials(diffuseYeollow);
		scene.addMaterials(diffuseBlue);
		scene.addMaterials(metalGold);
		scene.addMaterials(metalSilver);
	}

	// Configure Spheres
	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(0.f, -101.f, 0.f);
		sphere.Radius = 100.f;
		sphere.MatIndex = 0;
		scene.addSpheres(sphere);
	}
	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.Radius = 1.f;
		sphere.MatIndex = 1;
		scene.addSpheres(sphere);
	}
	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(2.01f, 0.0f, 0.0f);
		sphere.Radius = 1.f;
		sphere.MatIndex = 2;
		scene.addSpheres(sphere);
	}
	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(-2.01f, 0.0f, 0.0f);
		sphere.Radius = 1.f;
		sphere.MatIndex = 3;
		scene.addSpheres(sphere);
	}

	// Scene render specs
	scene.setSampleCount(10000);
	scene.setSampleBounces(100);

	// Camera setup
	camera.SetViewPortWidth(width);
	camera.SetViewPortHeight(height);
	camera.SetPosition(glm::vec3(0.f, 0.f, 8.f));
	camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f));
	camera.SetProjection(45.0f);
	camera.SetView();
	camera.CalculateRayDirections();
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