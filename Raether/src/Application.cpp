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
		redSpheres.Metallic = 0.0f;
		redSpheres.Roughness = 0.0f;

		scene.addMaterials(redSpheres);
	}
	{
		Material greenSpheres;
		greenSpheres.Albedo = glm::vec3(0.0f, 1.0f, 0.0f);
		greenSpheres.Metallic = 0.0f;
		greenSpheres.Roughness = 0.2f;

		scene.addMaterials(greenSpheres);
	}
	{
		Material blueSpheres;
		blueSpheres.Albedo = glm::vec3(0.0f, 0.0f, 1.0f);
		blueSpheres.Metallic = 0.0f;
		blueSpheres.Roughness = 0.3f;

		scene.addMaterials(blueSpheres);
	}
	{
		Material greySpheres;
		greySpheres.Albedo = glm::vec3(0.2f, 0.2f, 0.2f);
		greySpheres.Metallic = 0.0f;
		greySpheres.Roughness = 1.0f;

		scene.addMaterials(greySpheres);
	}

	// Configure spehers
	//{
	//	sphere.SphereOrigin = glm::vec3(-1.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 0;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 1;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.SphereOrigin = glm::vec3(1.0f, 0.0f, 0.0f);
	//	sphere.Radius = 0.5f;
	//	sphere.MatIndex = 2;
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}

	 // Configure spehers
	{
		sphere.SphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.Radius = 0.5f;
		sphere.MatIndex = 0;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(0.0f, -1000.5f, 0.0f);
		sphere.Radius = 1000.0f;
		sphere.MatIndex = 3;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(0.7f, -0.3f, 0.0f);
		sphere.Radius = 0.2f;
		sphere.MatIndex = 1;
		scene.addSpheres(sphere);
	}
	{
		sphere.SphereOrigin = glm::vec3(-0.85f, -0.2f, 0.0f);
		sphere.Radius = 0.3f;
		sphere.MatIndex = 2;
		scene.addSpheres(sphere);
	}

	// Camera setup
	camera.SetPosition(glm::vec3(0.0f, 0.5f, 2.5f));
	camera.SetOrientation(glm::vec3(0.0f, -0.30f, -1.2f));
	camera.SetViewPortWidth(width);
	camera.SetViewPortHeight(height);
	camera.SetProjection(45.0f, 0.1f, 100.0f);
	camera.SetView();
	camera.CalculateRayDirections();

	// Adding the light direction to the scene
	scene.Lightdirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
}

void App::run() {
	setUpScene();

	scene.SampleCount = 500;

	renderer.RenderLoop(rae, scene, camera);
}