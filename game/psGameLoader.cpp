#include "psGameLoader.h"


psGameLoader::psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups) : 
	m_fps(_fps), 
	m_ups(_ups),
	m_display(new psDisplay(width, height, title)),
	m_light(psLightSource(glm::vec3(1.f, 3.f, 4.f), glm::vec3(1.f, 0.9f, 0.87f), 1.f)),
	m_world(m_physicsCommon.createPhysicsWorld()) {

	m_world->setIsGravityEnabled(true);
	m_world->enableSleeping(false);
}

void psGameLoader::sub_render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader.bind();
	m_camera.updateProjectionMatrix(GAME_FOV, m_display->getWidth(), m_display->getHeight(), GAME_NEAR, GAME_FAR);
	m_shader.setUniform("projectionMatrix", m_camera.getProjectionMatrix());

	m_camera.updateViewMatrix();
	m_shader.setUniform("viewMatrix", m_camera.getViewMatrix());
	m_light.bind(m_shader);

	for (psEntity *entity : m_arrEntity) {
		entity->updatePos();
		m_shader.setUniform("modelMatrix", entity->getModelMatrix());
		entity->render(m_shader);
	}
	
	m_shader.unbind();

	m_gridshader.bind();
	m_gridshader.setUniform("projectionMatrix", m_camera.getProjectionMatrix());
	m_gridshader.setUniform("viewMatrix", m_camera.getViewMatrix());
	m_gridmodel->render(m_gridshader);
	m_gridshader.unbind();

	m_display->refresh();
}

unsigned int psGameLoader::setup() {

	// In the case something goes wrong and GLEW is working on it's edge.
	if (m_display->initContext() & (INIT_MISMATCH | WINDOW_CREATION_FAIL))
		return 1;

	m_shader.create();
	m_shader.setupVertexShader(readfile_s("resource/vertex.glsl"));
	m_shader.setupFragmentShader(readfile_s("resource/fragment.glsl"));
	m_shader.link();
	m_shader.buildUniform("projectionMatrix");
	m_shader.buildUniform("modelMatrix");
	m_shader.buildUniform("viewMatrix");
	m_shader.buildUniform("texture_diffuse1");
	m_light.createUniforms(m_shader);

	m_gridshader.create();
	m_gridshader.setupVertexShader(readfile_s("resource/grid_vertex.glsl"));
	m_gridshader.setupFragmentShader(readfile_s("resource/grid_fragment.glsl"));
	m_gridshader.link();
	m_gridshader.buildUniform("projectionMatrix");
	m_gridshader.buildUniform("viewMatrix");
	m_gridmodel = new psModel("resource/scene/plane.obj");
	m_commonModel = new psModel("resource/scene/obama/cube.obj");

	rp3d::Vector3 position(0.f, -1.0f, 0.f);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform {position, orientation};
	m_floor = m_world->createRigidBody(transform);
	m_floor->setType(rp3d::BodyType::STATIC);

	const rp3d::Vector3 halfExtents(25.f, 1.f, 25.f);
	rp3d::BoxShape *boxShape {m_physicsCommon.createBoxShape(halfExtents)};

	transform = rp3d::Transform::identity();
	m_floor->addCollider(boxShape, transform);

	return 0;
}

void psGameLoader::run() {

	float accumulator{0.f};
	//const float stepf{1.f / m_fps};
	const float stepu{1.f / m_ups};

	int iCount{0};
	bool isKeyGReleased{false};

	while (!m_display->shouldClose()) {
		accumulator += m_clock.getSequence();
		while (accumulator >= stepu) {
			//LOGICAL UPDATES HERE
			
			m_world->update(stepu);

			float x{0.f}, y{0.f}, z{0.f};
			if (m_display->isKeyPressed(GLFW_KEY_SPACE)) {
				y += 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
				y -= 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_W)) {
				z -= 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_S)) {
				z += 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_A)) {
				x -= 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_D)) {
				x += 0.05f;
			}

			if (m_display->isKeyPressed(GLFW_KEY_T)) {

				// Limiting 1 per stepu
				if (iCount < 1) {

					psEntity *entity = new psEntity(m_commonModel);

					rp3d::Transform entTransform = rp3d::Transform::identity();
					rp3d::Vector3 translation(0.f, 13.f, 0.f);
					entTransform.setPosition(translation);
					rp3d::RigidBody *rigidbody = m_world->createRigidBody(entTransform);
					const rp3d::Vector3 halfExtents1(1.f, 1.f, 1.f);
					rigidbody->addCollider(m_physicsCommon.createBoxShape(halfExtents1), rp3d::Transform::identity());
					entity->setBody(rigidbody);
					m_arrEntity.push_back(entity);

					++iCount;
				}
			}

			if (m_display->isKeyPressed(GLFW_KEY_G)) {

				if (isKeyGReleased) {

					if (!m_arrEntity.empty()) {

						auto &entity = m_arrEntity.back();
						m_world->destroyRigidBody(entity->getBody());

						entity->kill();
						delete entity;
						m_arrEntity.pop_back();
					}
					isKeyGReleased = false;
				}
			}

			if (m_display->isKeyReleased(GLFW_KEY_G)) {

				isKeyGReleased = true;
			}

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			m_camera.setRotation(m_display->getViewPitch(), m_display->getViewYaw(), 0.f);
			m_camera.move(x, y, z);
			accumulator -= stepu;
		}

		//float last = m_clock.getHook() + stepf;
		//if(m_clock.getSystemTime() >= last)
		sub_render();
		iCount = 0;
	}

}

void psGameLoader::terminate() {

	m_gridmodel->dispose();
	m_gridshader.dispose();
	for (auto &entity : m_arrEntity) {
		entity->kill();
		delete entity;
	}

	m_arrEntity.clear();

	m_world->destroyRigidBody(m_floor);

	m_commonModel->dispose();
	m_shader.dispose();
	m_display->dispose();
}