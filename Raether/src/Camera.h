#pragma once

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\simd\matrix.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Raether.h"
#include "Scene.h"

enum struct CamMotion { STATIC, MOVED, FOV };

class Camera
{
public:
	Camera();
	~Camera();

	void SetFocus(double strength, double distance);
	void SetFovRange(double minfov, double maxfov);
	void SetCamMovement(double motionsensitivity, double movementspeed);
	void SetJitterStrength(double jitterstrength);
	void SetPosition(glm::dvec3 position);
	void SetForwardDirection(glm::dvec3 forward);
	void SetViewPortWidth(uint32_t vp_Width);
	void SetViewPortHeight(uint32_t vp_Height);
	void SetProjection(double v_fov);
	void SetView();

	const uint32_t GetViewPortWidth() const { return viewportWidth; }
	const uint32_t GetViewPortHeight() const { return viewportHeight; }
	const glm::dvec3& GetPosition() const { return cameraOrigin; }
	const std::vector<glm::dvec3>& GetRayDirection() const { return rayDirections; }
	const double GetRayTime() const { return Utils::RandomDouble(); /* Ranges from 0.0 - 0.9999 */ }
	const double GetCamFovFraction() const { return (V_FOV / maxFov); /* Ranges From 0 - 1 */ }
	const double GetDefocusStrength() const { return defocusStrength; }
	const double GetFocusDistance() const { return focusDistance; };
	glm::dvec3 GetDefocusDiskSample() const;

	void CalculateRayDirections();
	void HandleInput(class Raether& rae);

private:

	uint32_t viewportWidth;
	uint32_t viewportHeight;

	double V_FOV;
	double defocusStrength;
	double focusDistance;

	double minFOV;
	double maxFOV;

	double motionSensitivity;
	double movementSpeed;

	double jitterStrength;

	glm::dvec3 cameraOrigin;
	glm::dvec3 cameraOrientation;
	glm::dvec3 forwardDirection;
	glm::dvec3 upDirection;
	glm::dvec3 rightDirection;

	glm::dmat4 projection;
	glm::dmat4 view;
	glm::dmat4 inverseProjection;
	glm::dmat4 inverseView;

	//Cached Ray Directions
	std::vector<glm::dvec3> rayDirections;
};