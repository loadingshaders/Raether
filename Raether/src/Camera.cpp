#include "Camera.h"

Camera::Camera() :
	viewportWidth(800),
	viewportHeight(800),
	V_FOV(45.0),
	defocusStrength(0.0),
	focusDistance(0.0),
	minFOV(minFov),
	maxFOV(maxFov),
	motionSensitivity(camMotionSensitivity),
	movementSpeed(camMovementSpeed),
	jitterStrength(JitterStrength),
	cameraOrigin(glm::dvec3(0.0, 0.0, -2.0)),
	forwardDirection(glm::dvec3(0.0, 0.0, -1.0)),
	cameraOrientation(cameraOrigin + forwardDirection),
	upDirection(glm::dvec3(0.0, 1.0, 0.0)),
	rightDirection(glm::dvec3(1.0, 0.0, 0.0)),
	projection(glm::dmat4(0.0)),
	view(glm::dmat4(0.0)),
	inverseProjection(glm::dmat4(0.0)),
	inverseView(glm::dmat4(0.0))
{}
Camera::~Camera() {}

void Camera::SetFocus(double strength, double distance) {
	defocusStrength = strength;
	focusDistance = distance;
}

void Camera::SetFovRange(double minfov, double maxfov) {
	minFOV = minfov;
	maxFOV = maxfov;
}

void Camera::SetCamMovement(double motionsensitivity, double movementspeed) {
	motionSensitivity = motionsensitivity;
	movementSpeed = movementspeed;
}

void Camera::SetJitterStrength(double jitterstrength) {
	jitterStrength = jitterstrength;
}

void Camera::SetPosition(glm::dvec3 position) { cameraOrigin = position; }
void Camera::SetForwardDirection(glm::dvec3 forward) { forwardDirection = forward; }
void Camera::SetViewPortWidth(uint32_t vp_Width) { viewportWidth = vp_Width; }
void Camera::SetViewPortHeight(uint32_t vp_Height) { viewportHeight = vp_Height; }
void Camera::SetProjection(double v_fov) {
	V_FOV = v_fov;
	projection = glm::perspectiveFov(glm::radians(V_FOV), (double)viewportWidth, (double)viewportHeight, camNearDist, camFarDist);
	inverseProjection = glm::inverse(projection);
}

void Camera::SetView() {
	cameraOrientation = cameraOrigin + forwardDirection;
	view = glm::lookAt(cameraOrigin, cameraOrientation, upDirection);
	inverseView = glm::inverse(view);
}

glm::dvec3 Camera::GetDefocusDiskSample() const {
	glm::dvec2 defocusJitter = Utils::RandomPointOnCircle() * (defocusStrength / viewportWidth);
	return cameraOrigin + rightDirection * defocusJitter.r + upDirection * defocusJitter.g;
}

void Camera::CalculateRayDirections() {
	rayDirections.resize((uint64_t)(viewportWidth * viewportHeight));

	for (uint32_t y = 0; y < viewportHeight; y++) {
		for (uint32_t x = 0; x < viewportWidth; x++) {
			glm::dvec2 coord = { x / (double)viewportWidth, y / (double)viewportHeight };
			coord = coord * 2.0 - 1.0; // -1 to 1

			glm::dvec4 target = inverseProjection * glm::dvec4(coord.x, coord.y, 1.0, 1.0);
			glm::dvec3 rayDirection = glm::dvec3(inverseView * glm::dvec4(glm::normalize(glm::dvec3(target) / target.w), 0.0));//world space
			rayDirections[(uint64_t)(x + y * viewportWidth)] = rayDirection;
		}
	}
}

void Camera::HandleInput(class Raether& rae) {

	rightDirection = glm::cross(forwardDirection, upDirection);

	CamMotion cam = CamMotion::STATIC;

	/// For Camera Movement
	if (rae.keyState == Keystate::W) {
		cameraOrigin += forwardDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::S) {
		cameraOrigin -= forwardDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::A) {
		cameraOrigin -= rightDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::D) {
		cameraOrigin += rightDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::Q) {
		cameraOrigin -= upDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::E) {
		cameraOrigin += upDirection * movementSpeed;
		cam = CamMotion::MOVED;
	}

	/// For Camera Rotation
	if (rae.mouseState == Mousestate::INMOTION) {
		if (rae.mouseDelta.x != 0.0 || rae.mouseDelta.y != 0.0) {

			double yawDelta = rae.mouseDelta.x * motionSensitivity;
			double pitchDelta = rae.mouseDelta.y * motionSensitivity;

			/// Don't really know what's happening here :/
			glm::dquat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
			forwardDirection = glm::rotate(q, forwardDirection);

			cam = CamMotion::MOVED;
		}
	}

	/// For Camera FOV
	if (rae.mouseState == Mousestate::SCROLLING) {

		V_FOV -= rae.scrollAmount * 1.5;

		if (V_FOV <= minFOV) {
			V_FOV = minFOV;
		}
		else if (V_FOV >= maxFOV) {
			V_FOV = maxFOV;
		}
		
		SetProjection(V_FOV);

		cam = CamMotion::MOVED;
	}


	if (cam == CamMotion::MOVED) {

		SetView();
		CalculateRayDirections();

		#if camDetails == 1

		Utils::PrintVec3("\ncamOrigin     : ", cameraOrigin);
		Utils::PrintVec3("\ncamOrientation: ", cameraOrientation);
		Utils::PrintVec3("\nForward       : ", forwardDirection);
		Utils::PrintVec2("\nV_FOV         : ", glm::vec2(V_FOV));
		Utils::PrintError("\n");

		#endif
	}
}