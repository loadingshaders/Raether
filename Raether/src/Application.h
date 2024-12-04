#pragma once

#include <iostream>
#include <inttypes.h>

#include <glm\glm.hpp>

#include "Raether.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include "Timer.h"
#include "Config.h"
#include "Sphere.h"
#include "Quad.h"
#include "Triangle.h"
#include "Box.h"
#include "Mesh.h"
#include "Volume.h"
#include "HittableList.h"

class App {
public:
	App();
	~App();

	void run();

private:
	void setWindow();
	void setUpScene();
	void updateScene();

private:
	const char* title;
	const int width;
	const int height;

	Raether rae;
	Scene scene;
	Camera camera;
	Renderer renderer;
};