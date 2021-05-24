#include "render_info.h"

void psMatrixStack::updateProjectionMatrix(float fov, float width, float height, float near, float far) {

	projectionMat = perspective(fov, width / height, near, far);
}

void psMatrixStack::updateModelMatrix(const vec3 &position, const vec3 &rotation, float scaling) {

	modelMat = translate(mat4(1.f), position);
	modelMat = rotate(modelMat, -rotation.x, vec3(1.f, 0.f, 0.f));
	modelMat = rotate(modelMat, -rotation.y, vec3(0.f, 1.f, 0.f));
	modelMat = rotate(modelMat, -rotation.z, vec3(0.f, 0.f, 1.f));
	modelMat = scale(modelMat, vec3(scaling));
}

void psMatrixStack::updateViewMatrix(const psActiveRenderInfo &ref) {

	vec3 pos = ref.getPosition();
	vec3 rot = ref.getRotation();
	viewMat = rotate(mat4(1.f), rot.x, vec3(1.f, 0.f, 0.f));
	viewMat = rotate(viewMat, rot.y, vec3(0.f, 1.f, 0.f));
	viewMat = rotate(viewMat, rot.z, vec3(0.f, 0.f, 1.f));
	viewMat = translate(viewMat, -pos);
}

psActiveRenderInfo::psActiveRenderInfo(const vec3 &pos, const vec3 &rot) {

	position = pos;
	rotation = rot;
}

void psActiveRenderInfo::setPosition(float _x, float _y, float _z) {

	position = vec3(_x, _y, _z);
}

void psActiveRenderInfo::move(float _x, float _y, float _z) {

	vec3 offset = vec3(_x, 0.f, _z);
	//offset = rotateX(offset, -rotation.x);
	offset = rotateY(offset, -rotation.y);
	// offset = rotateZ(offset, -rotation.z);
	offset.y = _y;
	position += offset;
}

void psActiveRenderInfo::setRotation(float _x, float _y, float _z) {

	rotation = vec3(_x, _y, _z);
}