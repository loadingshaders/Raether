#pragma once

#include <iostream>

#include <glm\glm.hpp>

#include "Raether.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"

class App
{
public:
	App();
	~App();

	void run();
private:
	const char* title;
	const int width;
	const int height;

	Raether rae;
	Scene scene;
	Sphere sphere;
	Camera camera;
	Renderer renderer;

	void setWindow();
	void setUpScene();
};
