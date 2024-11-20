#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\simd\matrix.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Raether.h"
#include "Scene.h"

enum struct CamMotion { STATIC, MOVED , FOV};

class Camera
{
public:
	Camera();
	~Camera();

	void SetFocus(float strength, float distance);
	void SetFovRange(float minfov, float maxfov);
	void SetCamMovement(float motionsensitivity, float movementspeed);
	void SetJitterStrength(float jitterstrength);
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
	const float GetRayTime() const { return Utils::RandomFloat(); /* Ranges from 0.0f - 0.99f */ }
	const float GetCamFovFraction() const { return (V_FOV / maxFov); /* Ranges From 0 - 1 */ }
	const float GetDefocusStrength() const { return defocusStrength; }
	const float GetFocusDistance() const { return focusDistance; };
	glm::vec3 GetDefocusDiskSample() const;

	void CalculateRayDirections();
	void HandleInput(class Raether& rae);

private:

	uint32_t viewportWidth;
	uint32_t viewportHeight;

	float V_FOV;
	float defocusStrength;
	float focusDistance;

	float minFOV;
	float maxFOV;

	float motionSensitivity;
	float movementSpeed;

	float jitterStrength;

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