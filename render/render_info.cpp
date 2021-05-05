#include "render_info.h"

void psMatrixStack::updateProjectionMatrix(float fov, float width, float height, float near, float far) {

	projectionMat.set(psMatrix4::_perspective(fov, width / height, near, far));
}

void psMatrixStack::updateModelViewMatrix(const psVector3 &position, const psVector3 &rotation, float scale) {

	psMatrix4 mat;
	mat.identity();
	mat.translate(position);
	mat.rotate(_frad(-rotation.x()), _frad(-rotation.y()), _frad(-rotation.z()));
	mat *= scale;
	modelViewMat.set(viewMat * mat);
}

void psMatrixStack::updateViewMatrix(const psActiveRenderInfo &ref) {

	psVector3 pos = ref.getPosition();
	psVector3 rot = ref.getRotation();
	viewMat.identity();
	viewMat.rotateX(_frad(rot.x()));
	viewMat.rotateY(_frad(rot.y()));
	viewMat.translate(-pos.x(), -pos.y(), -pos.z());
}

psActiveRenderInfo::psActiveRenderInfo(const psVector3 &pos, const psVector3 &rot) {

	position.set(pos);
	rotation.set(rot);
}

void psActiveRenderInfo::setPosition(float _x, float _y, float _z) {

	position.set(_x, _y, _z);
}

void psActiveRenderInfo::move(float _x, float _y, float _z) {

	if (_x) {
		position.addX(-sinf(_frad(rotation.y() - 90.f)) * _x);
		position.addZ(sinf(_frad(rotation.y() - 90.f)) * _x);
	}

	if (_z) {
		position.addX(-sinf(_frad(rotation.y())) * _z);
		position.addZ(sinf(_frad(rotation.y())) * _z);
	}

	position.addY(_y);
}

void psActiveRenderInfo::setRotation(float _x, float _y, float _z) {

	rotation.set(_x, _y, _z);
}

void psActiveRenderInfo::rotate(float _x, float _y, float _z) {

	rotation.add(_x, _y, _z);
}