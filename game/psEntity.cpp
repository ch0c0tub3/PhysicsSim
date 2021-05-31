#include "psEntity.hpp"

psEntity::psEntity(const char *filename) :
	m_model(new psModel(filename)) {

}

psEntity::~psEntity() {

	kill();
}

void psEntity::kill() {

	m_model->dispose();
}

void psEntity::updatePos() {

	m_transform = m_body->getTransform();
	m_pos = m_transform.getPosition();
	m_rotation = m_transform.getOrientation();
	
	updateModelMatrix();
}

void psEntity::updateModelMatrix() {

	float modelMatrix[4*4];
	m_transform.getOpenGLMatrix(modelMatrix);

	m_modelMat = glm::make_mat4(modelMatrix);
}

void psEntity::setBody(rp3d::RigidBody *body) {

	m_body = body;
}

void psEntity::setBodyType(const rp3d::BodyType &type) {
	
	m_body->setType(type);
}

void psEntity::setPosition(const rp3d::Vector3 &position) {

	const rp3d::Transform transform(position, m_rotation);
	m_body->setTransform(transform);
	updatePos();
}

void psEntity::setRotation(const rp3d::Quaternion &rotation) {

	const rp3d::Transform transform(m_pos, rotation);
	m_body->setTransform(transform);
	updatePos();
}

void psEntity::render(psShader &shader) {

	m_model->render(shader);
}