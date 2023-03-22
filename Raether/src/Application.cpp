#include "Application.h"

App::App() : rae(), scene(), sphere(), camera(), renderer() {
	title = "Raether";
	width = 900;
	height = 500;
}
App::~App() {
}

void App::setWindow() {
	rae.raeCreateWindow(title, width, height);
}

void App::setUpScene() {
	// Window Setup
	setWindow();

	// Configure spehers
	{
		sphere.sphereOrigin = glm::vec3(-1.0f, 0.0f, 0.0f);
		sphere.radius = 0.5f;
		sphere.albedo = glm::vec3(1.0f, 0.0f, 0.0f);
		// Add the Sphere to the scene
		scene.addSpheres(sphere);
	}
	{
		sphere.sphereOrigin = glm::vec3(1.0f, 0.0f, 0.0f);
		sphere.radius = 0.5f;
		sphere.albedo = glm::vec3(0.0f, 0.0f, 1.0f);
		// Add the Sphere to the scene
		scene.addSpheres(sphere);
	}
	{
		sphere.sphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
		sphere.radius = 0.5f;
		sphere.albedo = glm::vec3(0.0f, 1.0f, 0.0f);
		// Add the Sphere to the scene
		scene.addSpheres(sphere);
	}

	 // Configure spehers
	//{
	//	sphere.sphereOrigin = glm::vec3(0.0f, -30.5f, 0.0f);
	//	sphere.radius = 30.0f;
	//	sphere.albedo = glm::vec3(1.0f, 1.0f, 1.0f);
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}
	//{
	//	sphere.sphereOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	//	sphere.radius = 0.5f;
	//	sphere.albedo = glm::vec3(1.0f, 1.0f, 1.0f);
	//	// Add the Sphere to the scene
	//	scene.addSpheres(sphere);
	//}

	// Camera setup
	camera.SetPosition(glm::vec3(0.0f, 0.5f, 2.0f)); // 0.0f, 1.0f, 2.0f
	camera.SetOrientation(glm::vec3(0.0f, -0.3f, -1.2f)); // 0.0f, -0.5f, -1.0f
	camera.SetViewPortWidth(width);
	camera.SetViewPortHeight(height);
	camera.SetProjection(45.0f, 0.1f, 100.0f);
	camera.SetView();
	camera.CalculateRayDirections();

	// Adding the light direction to the scene
	scene.Lightdirection = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
}
void App::run() {
	setUpScene();

	auto start = logtime;

	renderer.Render(rae, scene, camera);

	auto end = logtime;
	std::cout << "Elapsed time: " << elapsed(end - start).count() << " ms" << std::endl;
	
	rae.raeRun();

	end = logtime;
	std::cout << "\nTotal Runtime: " << elapsed(end - start).count() << " ms" << std::endl;
}