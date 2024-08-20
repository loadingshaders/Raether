#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\simd\matrix.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Raether.h"
#include "Scene.h"

#define camMotionSensitivity 0.01f
#define camMovementSpeed 0.3f

enum struct CamMotion { STATIC, MOVED , FOV};

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position);
	void SetForwardDirection(glm::vec3 forward);
	void SetViewPortWidth(int vp_Width);
	void SetViewPortHeight(int vp_Height);
	void SetProjection(float v_fov);
	void SetView();

	const uint32_t GetViewPortWidth() const { return viewportWidth; }
	const uint32_t GetViewPortHeight() const { return viewportHeight; }
	const glm::vec3& GetPosition() const { return cameraOrigin; }
	const std::vector<glm::vec3>& GetRayDirection() const { return rayDirections; }

	void CalculateRayDirections();
	void HandleInput(class Raether& rae);

private:

	uint32_t viewportWidth;
	uint32_t viewportHeight;

	float V_FOV;

	glm::vec3 cameraOrigin;
	glm::vec3 cameraOrientation;
	glm::vec3 forwardDirection;
	glm::vec3 upDirection;
	glm::vec3 rightDirection;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 inverseProjection;
	glm::mat4 inverseView;

	//Cached Ray Directions
	std::vector<glm::vec3> rayDirections;
};