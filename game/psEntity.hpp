#ifndef PS_PROTOTYPE_ENTITY
#define PS_PROTOTYPE_ENTITY

#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/prot/psModel.h"
#include "render/prot/psLightSource.h"
#include "render/shader.hpp"

class psEntity {
protected:
	psModel				*m_model;

	rp3d::RigidBody		*m_body;
	rp3d::Vector3		m_pos;

	rp3d::Quaternion	m_rotation;
	rp3d::Transform		m_transform;

	glm::mat4 m_modelMat;

public:

	psEntity(psModel *model);
	~psEntity();

	void kill();

	const glm::mat4 &getModelMatrix() const {

		return m_modelMat;
	}

	void updatePos();
	void updateModelMatrix();

	void setBody(rp3d::RigidBody *body);
	const rp3d::RigidBody* getBody() const {
		return m_body;
	}

	void setBodyType(const rp3d::BodyType &type);

	void setPosition(const rp3d::Vector3 &position);
	const rp3d::Vector3 &getPos() const {
		return m_pos;
	}
	
	void setRotation(const rp3d::Quaternion &rotation);
	const rp3d::Quaternion &getRotation() const {
		return m_rotation;
	}

	void render(psShader& shader);

};

#endif // !PS_PROTOTYPE_ENTITY
