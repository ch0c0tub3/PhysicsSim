#include "psEntity.h"

psEntity::psEntity(glm::vec3 pos, float mass, psModel *model, psPhysicsWorld world) : m_model(model) {

	m_transform = glm::translate(mat4(1.f), pos);
	btCollisionShape *shape = m_model->get_btshape();
	//btCollisionShape *shape = new btBoxShape(btVector3(1.f, 1.f, 1.f));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	btScalar btmass(mass);
	btVector3 localInertia(0.f, 0.f, 0.f);
	if (mass)
		shape->calculateLocalInertia(btmass, localInertia);

	btMotionState *state = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo build(btmass, state, shape, localInertia);
	m_rigidBody = new btRigidBody(build);
	world.add_rigidbody(m_rigidBody);
}

void psEntity::tick(psPhysicsWorld world) {

	if (!m_rigidBody || !m_rigidBody->getMotionState())
		return;

	btTransform transform = m_rigidBody->getWorldTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	m_transform = glm::mat4(matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}

void psEntity::render(psMatrixStack &matrix_stack, psShader &shader) {

	matrix_stack.updateModelMatrix(m_transform, 1.f);
	shader.setUniform("modelMatrix", matrix_stack.getModelMatrix());
	m_model->render(shader);
}