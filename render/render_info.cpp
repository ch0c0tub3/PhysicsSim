#include "render_info.h"

void psMatrixStack::updateProjectionMatrix(float fov, float width, float height, float near, float far) {

	projectionMat = perspective(fov, width / height, near, far);
}

void psMatrixStack::updateModelViewMatrix(const vec3 &position, const vec3 &rotation, float scaling) {

	mat4 mat = translate(mat4(1.f), position);
	mat = rotate(mat, rotation.x, vec3(1.f, 0.f, 0.f));
	mat = rotate(mat, rotation.y, vec3(0.f, 1.f, 0.f));
	mat = rotate(mat, rotation.z, vec3(0.f, 0.f, 1.f));
	mat = scale(mat, vec3(scaling));
	modelViewMat = viewMat * mat;
}

void psMatrixStack::updateViewMatrix(const psActiveRenderInfo &ref) {

	vec3 pos = ref.getPosition();
	vec3 rot = ref.getRotation();
	viewMat = rotate(mat4(1.f), rot.x, vec3(1.f, 0.f, 0.f));
	viewMat = rotate(viewMat, rot.y, vec3(0.f, 1.f, 0.f));
	viewMat = translate(viewMat, vec3(-pos.x, -pos.y, -pos.z));
}

psActiveRenderInfo::psActiveRenderInfo(const vec3 &pos, const vec3 &rot) {

	position = pos;
	rotation = rot;
}

void psActiveRenderInfo::setPosition(float _x, float _y, float _z) {

	position = vec3(_x, _y, _z);
}

void psActiveRenderInfo::move(float _x, float _y, float _z) {

	if (_x) {
		position.x += -sinf(_frad(rotation.y - 90.f)) * _x;
		position.z += sinf(_frad(rotation.y - 90.f)) * _x;
	}

	if (_z) {
		position.x += -sinf(_frad(rotation.y)) * _z;
		position.z += sinf(_frad(rotation.y)) * _z;
	}

	position.y += _y;
}

void psActiveRenderInfo::setRotation(float _x, float _y, float _z) {

	rotation = vec3(_x, _y, _z);
}

void psActiveRenderInfo::rotate(float _x, float _y, float _z) {

	rotation += vec3(_x, _y, _z);
}