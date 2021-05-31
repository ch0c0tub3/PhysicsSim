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

	m_arrEntity.at(0)->updatePos();
	m_shader.setUniform("modelMatrix", m_arrEntity.at(0)->getModelMatrix());

	m_camera.updateViewMatrix();
	m_shader.setUniform("viewMatrix", m_camera.getViewMatrix());
	m_light.bind(m_shader);

	m_arrEntity.at(0)->render(m_shader);
	
	m_shader.unbind();
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

	rp3d::Vector3 position(0.f, 0.f, -10.f);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform {position, orientation};
	m_floor = m_world->createCollisionBody(transform);

	const rp3d::Vector3 halfExtents(25.f, 25.f, 2.f);
	rp3d::BoxShape *boxShape {m_physicsCommon.createBoxShape(halfExtents)};

	transform = rp3d::Transform::identity();
	m_floorCollider = m_floor->addCollider(boxShape, transform);

	m_arrEntity.push_back(new psEntity("resource/scene/Crysler_new_yorker_1980.obj"));
	
	rp3d::Vector3 entPos = rp3d::Vector3(0.f, 0.f, 0.f);
	rp3d::Quaternion entRot = rp3d::Quaternion::identity();
	rp3d::Transform entTransform  = rp3d::Transform(entPos, entRot);
	m_arrEntity.at(0)->setBody(m_world->createRigidBody(transform));
	//m_arrEntity.at(0)->setBodyType(rp3d::BodyType::STATIC);

	return 0;
}

void psGameLoader::run() {

	float accumulator{0.f};
	//const float stepf{1.f / m_fps};
	const float stepu{1.f / m_ups};
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

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			m_camera.setRotation(m_display->getViewPitch(), m_display->getViewYaw(), 0.f);
			m_camera.move(x, y, z);
			accumulator -= stepu;
		}

		float factor {accumulator / stepu};

		rp3d::Transform currTransform = m_arrEntity.at(0)->getBody()->getTransform();
		static rp3d::Transform prevTransform = currTransform;

		rp3d::Transform interpolatedTransform {rp3d::Transform::interpolateTransforms(prevTransform, currTransform, factor)};

		//float last = m_clock.getHook() + stepf;
		//if(m_clock.getSystemTime() >= last)
		sub_render();

		prevTransform = currTransform;

	}

}

void psGameLoader::terminate() {

	m_arrEntity.at(0)->kill();
	m_shader.dispose();
	m_display->dispose();
}