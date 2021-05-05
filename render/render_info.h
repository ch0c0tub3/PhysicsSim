#ifndef PS_RENDER_INFO_PROTOTYPE
#define PS_RENDER_INFO_PROTOTYPE

#include "util/math/psVector3.h"
#include "util/math/psMatrix4.h"

class psActiveRenderInfo {

protected:

	psVector3 position;
	psVector3 rotation;

public:

	psActiveRenderInfo() {}

	psActiveRenderInfo(const psVector3 &pos, const psVector3 &rot);

	const psVector3 &getPosition() const {

		return position;
	}

	void setPosition(float _x, float _y, float _z);

	void move(float _x, float _y, float _z);

	const psVector3 &getRotation() const {

		return rotation;
	}

	void setRotation(float _x, float _y, float _z);

	void rotate(float _x, float _y, float _z);

};

class psMatrixStack {

protected:

	psMatrix4 projectionMat;
	psMatrix4 modelViewMat;
	psMatrix4 viewMat;

public:

	psMatrixStack() {}

	// Const to prevent unsafe modifications.
	const psMatrix4 &getProjectionMatrix() const {

		return projectionMat;
	}

	void updateProjectionMatrix(float fov, float width, float height, float near, float far);

	const psMatrix4 &getModelViewMatrix() const {

		return modelViewMat;
	}

	void updateModelViewMatrix(const psVector3 &position, const psVector3 &rotation, float scale);

	const psMatrix4 &getViewMatrix() const {

		return viewMat;
	}

	void updateViewMatrix(const psActiveRenderInfo &ref);

};

#endif