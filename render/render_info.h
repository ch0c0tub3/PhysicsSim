#ifndef PS_RENDER_INFO_PROTOTYPE
#define PS_RENDER_INFO_PROTOTYPE

#include "util/math/psMath.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/rotate_vector.hpp"

using namespace glm;

class psActiveRenderInfo {

protected:

	vec3 position;
	vec3 rotation;

public:

	psActiveRenderInfo() {}

	psActiveRenderInfo(const vec3 &pos, const vec3 &rot);

	const vec3 &getPosition() const {

		return position;
	}

	void setPosition(float _x, float _y, float _z);

	void move(float _x, float _y, float _z);

	const vec3 &getRotation() const {

		return rotation;
	}

	void setRotation(float _x, float _y, float _z);

};

class psMatrixStack {

protected:

	mat4 projectionMat;
	mat4 modelMat;
	mat4 viewMat;

public:

	psMatrixStack() {}

	// Const to prevent unsafe modifications.
	const mat4 &getProjectionMatrix() const {

		return projectionMat;
	}

	void updateProjectionMatrix(float fov, float width, float height, float near, float far);

	const mat4 &getModelMatrix() const {

		return modelMat;
	}

	void updateModelMatrix(const vec3 &position, const vec3 &rotation, float scale);

	const mat4 &getViewMatrix() const {

		return viewMat;
	}

	void updateViewMatrix(const psActiveRenderInfo &ref);

};

#endif