#pragma once

struct Hitrec {
	glm::vec3 HitPoint;
	glm::vec3 SurfaceNormal;
	glm::vec3 HitColor;
	int HitObjId;
	bool FrontFace;

	void SetFrontFace(const glm::vec3& rayDirection, glm::vec3& normal) {
		if (glm::dot(rayDirection, normal) > 0.f) {
			FrontFace = false;
		}
		else {
			FrontFace = true;
		}
		normal = FrontFace ? (normal) : (-normal);
	}
};