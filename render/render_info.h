#ifndef PS_RENDER_INFO_PROTOTYPE
#define PS_RENDER_INFO_PROTOTYPE

#include "util/math/psMath.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
//#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/rotate_vector.hpp"

class psActiveRenderInfo {

protected:

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::mat4 m_projectionMat;
	glm::mat4 m_viewMat;

public:

	psActiveRenderInfo() {}

	psActiveRenderInfo(const glm::vec3 &pos, const glm::vec3 &rot);

	const glm::vec3 &getPosition() const {

		return m_position;
	}

	void setPosition(const float &_x, const float &_y, const float &_z);

	void move(const float &_x, const float &_y, const float &_z);

	const glm::vec3 &getRotation() const {

		return m_rotation;
	}

	void setRotation(const float &_x, const float &_y, const float &_z);

	// Const to prevent unsafe modifications.
	const glm::mat4 &getProjectionMatrix() const {

		return m_projectionMat;
	}

	const glm::mat4 &getViewMatrix() const {

		return m_viewMat;
	}

	void updateProjectionMatrix(const float &fov, const float &width, const float &height, const float &near, const float &far);
	void updateViewMatrix();

};

#endif