	#include "render_info.h"

void psActiveRenderInfo::updateProjectionMatrix(const float &fov, const float &width, const float &height, const float &near, const float &far) {

	m_projectionMat = glm::perspective(fov, width / height, near, far);
}

void psActiveRenderInfo::updateViewMatrix() {

	glm::vec3 pos = m_position;
	glm::vec3 rot = m_rotation;
	m_viewMat = glm::rotate(glm::mat4(1.f), rot.x, glm::vec3(1.f,0.f,0.f));
	m_viewMat = glm::rotate(m_viewMat, rot.y, glm::vec3(0.f,1.f,0.f));
	m_viewMat = glm::rotate(m_viewMat, rot.z, glm::vec3(0.f,0.f,1.f));
	m_viewMat = glm::translate(m_viewMat, -pos);
}

psActiveRenderInfo::psActiveRenderInfo(const glm::vec3 &pos, const glm::vec3 &rot) : 
	m_position(pos),
	m_rotation(rot) {

}

void psActiveRenderInfo::setPosition(const float &_x, const float &_y, const float &_z) {

	m_position = glm::vec3(_x, _y, _z);
}

void psActiveRenderInfo::move(const float &_x, const float &_y, const float &_z) {

	glm::vec3 offset = glm::vec3(_x, 0.f, _z);
	offset = glm::rotateX(offset, -m_rotation.x);
	offset = glm::rotateY(offset, -m_rotation.y);
	offset = glm::rotateZ(offset, -m_rotation.z);
	offset.y += _y;
	if (offset.x || offset.y || offset.z)
		offset = normalize(offset);

	m_position += offset * 0.1f;
}

void psActiveRenderInfo::setRotation(const float &_x, const float &_y, const float &_z) {

	m_rotation = glm::vec3(_x, _y, _z);
}