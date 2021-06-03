#include "psPhysicsWorld.h"

psPhysicsWorld::psPhysicsWorld(glm::vec3 gravity, float time_step) {

	assert(time_step > 0.f);
	m_info.gravity = gravity;
	m_info.time_step = time_step;
}

void psPhysicsWorld::setup_physics() {

	m_broadphase = new btDbvtBroadphase();
	m_configuration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_configuration);
	m_solver = new btSequentialImpulseConstraintSolver();
	m_dworld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_configuration);
	m_dworld->setGravity(btVector3(m_info.gravity.x, m_info.gravity.y, m_info.gravity.z));
	btStaticPlaneShape *shape = new btStaticPlaneShape(btVector3(0.f, 1.f, 0.f), 0.f);
	btRigidBody *body = new btRigidBody(0.f, new btDefaultMotionState(), shape);
	body->setFriction(0.89f);
	body->setCollisionFlags(btCollisionObject::CollisionFlags::CF_STATIC_OBJECT | body->getCollisionFlags());
	m_dworld->addRigidBody(body);
}

void psPhysicsWorld::add_rigidbody(btRigidBody *rigidbody) {

	m_dworld->addRigidBody(rigidbody);
}

void psPhysicsWorld::remove_rigidbody(btRigidBody *rigidbody) {

	m_dworld->removeRigidBody(rigidbody);
}

void psPhysicsWorld::update(float partial_ticks, psMatrixStack &matrix_stack) {

	if (m_dworld)
		m_dworld->stepSimulation(1.f, glm::clamp((int)glm::round(partial_ticks * 0.1f), 1, 100));

}

void psPhysicsWorld::dispose() {

	/*size_t num = m_dworld->getNumCollisionObjects();
	for (size_t i = 0; i < num; i++) {
		btCollisionObject *object = m_dworld->getCollisionObjectArray()[i];
		if (object->getInternalType() == btCollisionObject::CollisionObjectTypes::CO_RIGID_BODY)
			delete btRigidBody::upcast(object)->getMotionState();

		delete object->getCollisionShape();
		m_dworld->removeCollisionObject(object);
		delete object;
	}*/

	delete m_dworld;
}