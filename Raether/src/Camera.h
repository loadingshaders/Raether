#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Raether.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position);
	void SetOrientation(glm::vec3 orientation);
	void SetViewPortWidth(int vp_Width);
	void SetViewPortHeight(int vp_Height);
	void SetMotionSensitivity(float sensitivity);

	void SetProjection(float cv_fov, float nearclip, float farclip);
	void SetView();
	

	const int GetViewPortWidth() const { return (int)viewportWidth; }
	const int GetViewPortHeight() const { return (int)viewportHeight; }
	
	const glm::vec3& GetPosition() const { return cameraOrigin; }
	const glm::vec3& GetOrientation() const { return cameraOrientation; }

	const glm::mat4& GetProjection() const { return projection; }
	const glm::mat4& GetInverseProjMatrix() const { return inverseProjection; }
	const glm::mat4& GetInverseViewMatrix() const { return inverseView; }

	const std::vector<glm::vec3>& GetRayDirection() const { return rayDirections; }

	void CalculateRayDirections();
private:

	uint32_t viewportWidth = 700;
	uint32_t viewportHeight = 620;

	float V_FOV;
	float aspect = (float)viewportWidth / (float)viewportHeight;
	float nearClip;
	float farClip;

	float camMotionSensitivity;

	glm::vec3 cameraOrigin{ 0.0f, 0.0f, 1.0f };
	glm::vec3 cameraOrientation{ 0.0f, 0.0f, -1.0f };
	glm::vec3 forwardDirection;
	glm::vec3 upDirection{ 0.0f, 1.0f, 0.0f };

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 inverseProjection;
	glm::mat4 inverseView;

	//Cached Ray Directions
	std::vector<glm::vec3> rayDirections;
};