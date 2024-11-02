#include "Camera.h"

Camera::Camera() : viewportWidth(700),
				   viewportHeight(620),
				   V_FOV(45.f),
				   defocusStrength(0.f),
				   focusDistance(0.f),
				   cameraOrigin(glm::vec3(0.f, 0.f, -2.f)),
				   forwardDirection(glm::vec3(0.f, 0.f, -1.f)),
				   cameraOrientation(cameraOrigin + forwardDirection),
				   upDirection(glm::vec3(0.f, 1.f, 0.f)),
				   rightDirection(glm::vec3(1.f, 0.f, 0.f)),
				   projection(glm::mat4(0.0f)),
				   view(glm::mat4(0.0f)),
				   inverseProjection(glm::mat4(0.0f)),
				   inverseView(glm::mat4(0.0f))
{
}
Camera::~Camera() { }

void Camera::SetFocus(float strength, float distance) {
	defocusStrength = strength;
	focusDistance = distance;
}

void Camera::SetPosition(glm::vec3 position) { cameraOrigin = position; }
void Camera::SetForwardDirection(glm::vec3 forward) { forwardDirection = forward; }
void Camera::SetViewPortWidth(int vp_Width) { viewportWidth = vp_Width; }
void Camera::SetViewPortHeight(int vp_Height) { viewportHeight = vp_Height; }
void Camera::SetProjection(float v_fov) {
	V_FOV = v_fov;
	projection = glm::perspectiveFov(glm::radians(V_FOV), (float)viewportWidth, (float)viewportHeight, (float)nearDist, (float)farDist);
	inverseProjection = glm::inverse(projection);
}

void Camera::SetView() {
	cameraOrientation = cameraOrigin + forwardDirection;
	view = glm::lookAt(cameraOrigin, cameraOrientation, upDirection);
	inverseView = glm::inverse(view);
}

glm::vec3 Camera::GetDefocusDiskSample() const {
	glm::vec2 defocusJitter = Utils::RandomPointOnCircle() * (defocusStrength / viewportWidth);
	return cameraOrigin + rightDirection * defocusJitter.r + upDirection * defocusJitter.g;
}

void Camera::CalculateRayDirections() {
	rayDirections.resize((uint64_t)(viewportWidth * viewportHeight));

	for (uint32_t y = 0; y < viewportHeight; y++) {
		for (uint32_t x = 0; x < viewportWidth; x++) {
			glm::vec2 coord = { (float)x / (float)viewportWidth, (float)y / (float)viewportHeight };
			coord = coord * 2.0f - 1.0f; // -1 to 1

			glm::vec4 target = inverseProjection * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
			glm::vec3 rayDirection = glm::vec3 ( inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));//world space
			rayDirections[(uint64_t)(x + y * viewportWidth)] = rayDirection;
		}
	}
}

void Camera::HandleInput(class Raether& rae) {

	rightDirection = glm::cross(forwardDirection, upDirection);

	CamMotion cam = CamMotion::STATIC;

	/// For Camera Movement
	if (rae.keyState == Keystate::W) {
		cameraOrigin += forwardDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::S) {
		cameraOrigin -= forwardDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::A) {
		cameraOrigin -= rightDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::D) {
		cameraOrigin += rightDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}
	if (rae.keyState == Keystate::Q) {
		cameraOrigin -= upDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}
	else if (rae.keyState == Keystate::E) {
		cameraOrigin += upDirection * camMovementSpeed;
		cam = CamMotion::MOVED;
	}

	/// For Camera Rotation
	if (rae.mouseState == Mousestate::INMOTION) {
		if (rae.mouseDelta.x != 0.0f || rae.mouseDelta.y != 0.0f) {

			float yawDelta = rae.mouseDelta.x * camMotionSensitivity;
			float pitchDelta = rae.mouseDelta.y * camMotionSensitivity;

			/// Don't really know what's happening here :/
			glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
			forwardDirection = glm::rotate(q, forwardDirection);

			cam = CamMotion::MOVED;
		}
	}

	/// For Camera FOV
	if (rae.mouseState == Mousestate::SCROLLING) {

		V_FOV -= rae.scrollAmount * 1.5f;
		if(V_FOV <= minFov) {
			V_FOV = minFov;
		}
		else if (V_FOV >= maxFov) {
			V_FOV = maxFov;
		}
		SetProjection(V_FOV);

		cam = CamMotion::MOVED;
	}


	if (cam == CamMotion::MOVED) {
		SetView();
		CalculateRayDirections();

		/*
		Utils::PrintVec3("camOrigin", cameraOrigin);
		Utils::PrintVec3("camOrientation", cameraOrientation);
		Utils::PrintVec3("Forward", forwardDirection);
		Utils::PrintVec2("V_FOV", glm::vec2(V_FOV));
		*/
	}
}