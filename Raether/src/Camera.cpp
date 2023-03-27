#include "Camera.h"

Camera::Camera() {
}
Camera::~Camera() {
}

void Camera::SetPosition(glm::vec3 position) { cameraOrigin = position; }
void Camera::SetOrientation(glm::vec3 orientation) { cameraOrientation = orientation; }
void Camera::SetViewPortWidth(int vp_Width) { viewportWidth = vp_Width; }
void Camera::SetViewPortHeight(int vp_Height) { viewportHeight = vp_Height; }

void Camera::SetProjection(float cv_fov, float n_Clip, float f_Clip) {
	V_FOV = cv_fov;
	// aspect = (float)viewportWidth / (float)viewportHeight;
	nearClip = n_Clip;
	farClip = f_Clip;

	projection = glm::perspectiveFov(glm::radians(V_FOV), (float)viewportWidth, (float)viewportHeight, nearClip, farClip);
	inverseProjection = glm::inverse(projection);
}
void Camera::SetView() {
	forwardDirection = cameraOrigin + cameraOrientation;
	view = glm::lookAt(cameraOrigin, forwardDirection, upDirection);
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