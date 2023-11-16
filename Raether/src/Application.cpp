#include "Application.h"

App::App() : width(900), height(500), rae(), scene(), sphere(), camera(), renderer() {
	title = "Raether";
}
App::~App() {
}

void App::setWindow() {
	rae.raeCreateWindow(title, width, height);
}

void App::setUpScene() {
	// Window Setup
	setWindow();

	// Configure Materials
	{
		Material redSpheres;
		redSpheres.Albedo = glm::vec3(1.0f, 0.0f, 0.0f);

		redSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		redSpheres.EmissionStrength = 0.0f;

		redSpheres.Metallic = 0.0f;
		redSpheres.Roughness = 0.0f;

		scene.addMaterials(redSpheres);
	}
	{
		Material greenSpheres;
		greenSpheres.Albedo = glm::vec3(0.0f, 1.0f, 0.0f);

		greenSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		greenSpheres.EmissionStrength = 0.0f;

		greenSpheres.Metallic = 0.0f;
		greenSpheres.Roughness = 0.2f;

		scene.addMaterials(greenSpheres);
	}
	{
		Material blueSpheres;
		blueSpheres.Albedo = glm::vec3(0.0f, 0.0f, 1.0f);

		blueSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		blueSpheres.EmissionStrength = 0.0f;

		blueSpheres.Metallic = 0.0f;
		blueSpheres.Roughness = 0.3f;

		scene.addMaterials(blueSpheres);
	}
	{
		Material whiteSpheres;
		whiteSpheres.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

		whiteSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		whiteSpheres.EmissionStrength = 0.0f;

		whiteSpheres.Metallic = 0.0f;
		whiteSpheres.Roughness = 1.0f;

		scene.addMaterials(whiteSpheres);
	}
	{
		Material lightSpheres;
		lightSpheres.Albedo = glm::vec3(0.0f, 0.0f, 0.0f);

		lightSpheres.EmissionColor = glm::vec3(1.0f, 1.0f, 1.0f);
		lightSpheres.EmissionStrength = 1.5f;

		lightSpheres.Metallic = 0.0f;
		lightSpheres.Roughness = 1.0f;

		scene.addMaterials(lightSpheres);
	}

	{
		Material redEmissiveSpheres;
		redEmissiveSpheres.Albedo = glm::vec3(0.0f, 0.0f, 0.0f);

		redEmissiveSpheres.EmissionColor = glm::vec3(1.0f, 0.0f, 0.0f);
		redEmissiveSpheres.EmissionStrength = 3.0f;

		redEmissiveSpheres.Metallic = 0.0f;
		redEmissiveSpheres.Roughness = 1.0f;

		scene.addMaterials(redEmissiveSpheres);
	}
	{
		Material greenEmissiveSpheres;
		greenEmissiveSpheres.Albedo = glm::vec3(0.0f, 0.0f, 0.0f);

		greenEmissiveSpheres.EmissionColor = glm::vec3(0.0f, 1.0f, 0.0f);
		greenEmissiveSpheres.EmissionStrength = 3.0f;

		greenEmissiveSpheres.Metallic = 0.0f;
		greenEmissiveSpheres.Roughness = 1.0f;

		scene.addMaterials(greenEmissiveSpheres);
	}
	{
		Material blueEmissiveSpheres;
		blueEmissiveSpheres.Albedo = glm::vec3(0.0f, 0.0f, 0.0f);

		blueEmissiveSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 1.0f);
		blueEmissiveSpheres.EmissionStrength = 3.0f;

		blueEmissiveSpheres.Metallic = 0.0f;
		blueEmissiveSpheres.Roughness = 1.0f;

		scene.addMaterials(blueEmissiveSpheres);
	}


	{
		Material whiteSpheres;
		whiteSpheres.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

		whiteSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		whiteSpheres.EmissionStrength = 0.0f;

		whiteSpheres.Metallic = 0.0f;
		whiteSpheres.Roughness = 0.0f;

		scene.addMaterials(whiteSpheres);
	}
	{
		Material whiteSpheres;
		whiteSpheres.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

		whiteSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		whiteSpheres.EmissionStrength = 0.0f;

		whiteSpheres.Metallic = 0.0f;
		whiteSpheres.Roughness = 0.5f;

		scene.addMaterials(whiteSpheres);
	}
	{
		Material whiteSpheres;
		whiteSpheres.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);

		whiteSpheres.EmissionColor = glm::vec3(0.0f, 0.0f, 0.0f);
		whiteSpheres.EmissionStrength = 0.0f;

		whiteSpheres.Metallic = 0.0f;
		whiteSpheres.Roughness = 1.0f;

		scene.addMaterials(whiteSpheres);
	}
	// Configure spehers
	//{
	//	sphere.SphereOrigin = glm::vec3(-1.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 6;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 7;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.SphereOrigin = glm::vec3(1.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 8;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.SphereOrigin = glm::vec3(-2.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 9;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}


	{
		sphere.SphereOrigin = glm::vec3(0.0f, -1000.5f, 0.0f);
		sphere.Radius = 1000.0f;
		sphere.MatIndex = 3;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.Radius = 0.5f;
		sphere.MatIndex = 10;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(0.7f, -0.3f, 0.0f);
		sphere.Radius = 0.2f;
		sphere.MatIndex = 9;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-0.85f, -0.2f, 0.0f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 8;
		scene.addSpheres(sphere);
	}
	/*{
		sphere.SphereOrigin = glm::vec3(-0.70f, 1.65f, -1.0f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 4;
		scene.addSpheres(sphere);
	}*/
	/*{
		sphere.SphereOrigin = glm::vec3(70.70f, 70.65f, 70.0f);
		sphere.Radius = 30.0f;
		sphere.MatIndex = 4;
		scene.addSpheres(sphere);
	}*/
	{
		sphere.SphereOrigin = glm::vec3(25.70f, 30.65f, 30.0f);
		sphere.Radius = 30.0f;
		sphere.MatIndex = 4;
		scene.addSpheres(sphere);
	}

	{
		sphere.SphereOrigin = glm::vec3(1.2f, -0.2f, -1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 5;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(1.2f, -0.2f, 1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 6;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-1.2f, -0.2f, -1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 7;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-1.2f, -0.2f, 1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 5;
		scene.addSpheres(sphere);
	}

	{
		sphere.SphereOrigin = glm::vec3(1.2f, 1.2f, -1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 5;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(1.2f, 1.2f, 1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 6;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-1.2f, 1.2f, -1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 7;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-1.2f, 1.2f, 1.3f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 5;
		scene.addSpheres(sphere);
	}

	// Camera setup
	camera.SetPosition(glm::vec3(0.0f, 0.3f, 2.5f));
	camera.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f));
	camera.SetViewPortWidth(width);
	camera.SetViewPortHeight(height);

	camera.SetMotionSensitivity(0.01f);
	camera.SetMovementSpeed(0.3f);

	camera.SetProjection(45.0f, 0.1f, 100.0f);
	camera.SetView();
	camera.CalculateRayDirections();

	// Scene setup
	scene.SampleCount = 10000;
	scene.Bounces = 10;
}

void App::updateScene() {
	renderer.Init(rae, scene, camera);

	// Main event loop
	while (rae.windowState == RaeState::ACTIVE) {

		/// Start the render
		rae.raeRenderBegin();

		/// Check for input
		if (rae.raeInputEvents()) {
			camera.HandleMouseInput(rae);
			renderer.ResetFrameIdx();
		}

		/// Render the scene
		renderer.Render(scene, camera);

		/// End the render
		rae.raeRenderEnd();
	}
}

void App::run() {
	setUpScene();
	updateScene();
}