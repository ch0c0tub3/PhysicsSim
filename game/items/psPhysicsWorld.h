#ifndef PS_PHYSICS_WORLD_PROTOTYPE
#define PS_PHYSICS_WORLD_PROTOTYPE

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"
#include "render/render_info.h"

typedef struct {

	glm::vec3 gravity;
	float time_step;
} construction_info;

class psPhysicsWorld {

protected:

	btDynamicsWorld *m_dworld;
	btBroadphaseInterface *m_broadphase;
	btCollisionConfiguration *m_configuration;
	btCollisionDispatcher *m_dispatcher;
	btConstraintSolver *m_solver;
	construction_info m_info;

public:

	psPhysicsWorld(glm::vec3 gravity, float time_step);

	~psPhysicsWorld() {

	}

	const btDynamicsWorld *getPhysics() {

		return m_dworld;
	}

	void setup_physics();

	void add_rigidbody(btRigidBody *rigidbody);

	void remove_rigidbody(btRigidBody *rigidbody);

	void update(float partial_ticks, psMatrixStack &matrix_stack);

	void dispose();

};

#endif