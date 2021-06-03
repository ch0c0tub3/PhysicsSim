#ifndef PS_ENTITY_PROTOTYPE
#define PS_ENTITY_PROTOTYPE

#include "btBulletDynamicsCommon.h"
#include "render/prot/psModel.h"
#include "render/render_info.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "psPhysicsWorld.h"

class psEntity {

protected:

	glm::mat4 m_transform;
	psModel *m_model;
	btRigidBody *m_rigidBody;

public:

	psEntity(glm::vec3 pos, float mass, psModel *model, psPhysicsWorld world);

	void tick(psPhysicsWorld world);

	void render(psMatrixStack &matrix_stack, psShader &shader);

};

#endif