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
		Material whiteSpheres;
		whiteSpheres.Albedo = glm::vec3(1.f);
		whiteSpheres.EmissionColor = glm::vec3(0.f, 0.f, 0.f);
		whiteSpheres.EmissionStrength = 0.f;
		whiteSpheres.Metallic = 0.f;
		whiteSpheres.Roughness = 0.f;

		scene.addMaterials(whiteSpheres);
	}

	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.Radius = 1.f;
		sphere.MatIndex = 0;
		scene.addSpheres(sphere);
	}
	{
		Sphere sphere;
		sphere.SphereOrigin = glm::vec3(0.f, -101.f, 0.f);
		sphere.Radius = 100.f;
		sphere.MatIndex = 0;
		scene.addSpheres(sphere);
	}

	// Scene render specs
	scene.setSampleCount(100);
	scene.setSampleBounces(10);

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