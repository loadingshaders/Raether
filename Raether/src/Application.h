#pragma once

#include <iostream>
#include <chrono>

#include <glm\glm.hpp>

#include "Raether.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"

#define logtime std::chrono::steady_clock::now()
#define elapsed std::chrono::duration_cast<std::chrono::milliseconds>


class App
{
public:
	App();
	~App();

	void run();
private:
	const char* title;
	int width;
	int height;

	Raether rae;
	Scene scene;
	Sphere sphere;
	Camera camera;
	Renderer renderer;

	void setWindow();
	void setUpScene();
};
