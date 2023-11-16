#include "Camera.h"

Camera::Camera() {
	cameraOrigin = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
	forwardDirection = glm::vec3(cameraOrigin + cameraOrientation);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	rightDirection = glm::cross(forwardDirection, upDirection);
}
Camera::~Camera() {
}

void Camera::SetPosition(glm::vec3 position) { cameraOrigin = position; }
void Camera::SetForwardDirection(glm::vec3 forward) { forwardDirection = forward; }
void Camera::SetViewPortWidth(int vp_Width) { viewportWidth = vp_Width; }
void Camera::SetViewPortHeight(int vp_Height) { viewportHeight = vp_Height; }

void Camera::SetMotionSensitivity(float sensitivity) { camMotionSensitivity = sensitivity; }
void Camera::SetMovementSpeed(float spd) { speed = spd; }

void Camera::SetProjection(float cv_fov, float n_Clip, float f_Clip) {
	V_FOV = cv_fov;
	// aspect = (float)viewportWidth / (float)viewportHeight;
	nearClip = n_Clip;
	farClip = f_Clip;

	projection = glm::perspectiveFov(glm::radians(V_FOV), (float)viewportWidth, (float)viewportHeight, nearClip, farClip);
	inverseProjection = glm::inverse(projection);
}
void Camera::SetView() {
	cameraOrientation = cameraOrigin + forwardDirection;
	view = glm::lookAt(cameraOrigin, cameraOrientation, upDirection);
	inverseView = glm::inverse(view);
}

void Camera::CalculateRayDirections() {
	rayDirections.resize(viewportWidth * viewportHeight);

	for (uint32_t y = 0; y < viewportHeight; y++) {
		for (uint32_t x = 0; x < viewportWidth; x++) {
			glm::vec2 coord = { (float)x / (float)viewportWidth, (float)y / (float)viewportHeight };
			coord = coord * 2.0f - 1.0f; // -1 to 1

			glm::vec4 target = inverseProjection * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
			glm::vec3 rayDirection = glm::vec3 ( inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));//world space
			rayDirections[x + y * viewportWidth] = rayDirection;
		}
	}
}

void Camera::HandleMouseInput(class Raether& rae) {

	rightDirection = glm::cross(forwardDirection, upDirection);

	CamMotion cam = CamMotion::STATIC;

	/// For Camera Movement
	if (rae.keyState == Keystate::W) {
		cameraOrigin += forwardDirection * speed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::S) {
		cameraOrigin -= forwardDirection * speed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::A) {
		cameraOrigin -= rightDirection * speed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::D) {
		cameraOrigin += rightDirection * speed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::Q) {
		cameraOrigin -= upDirection * speed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::E) {
		cameraOrigin += upDirection * speed;
		cam = CamMotion::MOVED;
	}

	/// For Camera Rotation
	if (rae.mouseState == Mousestate::INMOTION) {
		if (rae.delta.x != 0.0f || rae.delta.y != 0.0f) {

			float yawDelta = rae.delta.x * camMotionSensitivity;
			float pitchDelta = rae.delta.y * camMotionSensitivity;

			/// Don't really know what's happening here :/
			glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
			forwardDirection = glm::rotate(q, forwardDirection);

			cam = CamMotion::MOVED;
		}
	}

	/// For Camera FOV
	if (rae.mouseState == Mousestate::SCROLLING) {

		V_FOV -= rae.scrollAmount * 1.5f;
		if(V_FOV <= 1.0f) {
			V_FOV = 1.0f;
		}
		else if (V_FOV >= 179.0f) {
			V_FOV = 179.0f;
		}
		SetProjection(V_FOV, nearClip, farClip);

		cam = CamMotion::MOVED;
	}


	if (cam == CamMotion::MOVED) {
		SetView();
		CalculateRayDirections();
	}
}
