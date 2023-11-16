#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\simd\matrix.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Raether.h"

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

	void SetMotionSensitivity(float sensitivity);
	void SetMovementSpeed(float speed);

	void SetProjection(float cv_fov, float nearclip, float farclip);
	void SetView();
	

	const int GetViewPortWidth() const { return (int)viewportWidth; }
	const int GetViewPortHeight() const { return (int)viewportHeight; }
	
	const glm::vec3& GetPosition() const { return cameraOrigin; }
	/*const glm::vec3& GetOrientation() const { return cameraOrientation; }

	const glm::mat4& GetProjection() const { return projection; }
	const glm::mat4& GetInverseProjMatrix() const { return inverseProjection; }
	const glm::mat4& GetInverseViewMatrix() const { return inverseView; }*/

	const std::vector<glm::vec3>& GetRayDirection() const { return rayDirections; }

	void CalculateRayDirections();

	void HandleMouseInput(class Raether& rae);

private:

	uint32_t viewportWidth = 700;
	uint32_t viewportHeight = 620;

	float V_FOV;
	float aspect = (float)viewportWidth / (float)viewportHeight;
	float nearClip;
	float farClip;
	float camMotionSensitivity;
	float speed;

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