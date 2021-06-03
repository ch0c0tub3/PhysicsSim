#include "psGameLoader.h"
#include "util/psFileLoader.h"

psGameLoader::psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups) : m_fps(_fps), m_ups(_ups),
m_display(new psDisplay(width, height, title)), m_light(psLightSource(glm::vec3(1.f, 3.f, 4.f), glm::vec3(1.f, 0.9f, 0.87f), 1.f)),
m_physics(psPhysicsWorld(glm::vec3(0.f, -9.801f, 0.f), 1.f / m_ups)) {

}

void psGameLoader::sub_render() {

	m_matrixStack.updateProjectionMatrix(GAME_FOV, m_display->getWidth(), m_display->getHeight(), GAME_NEAR, GAME_FAR);
	m_matrixStack.updateViewMatrix(m_camera);

	m_buffer_loader.bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Floor render
	m_gridshader.bind();
	m_gridshader.setUniform("projectionMatrix", m_matrixStack.getProjectionMatrix());
	m_gridshader.setUniform("viewMatrix", m_matrixStack.getViewMatrix());
	m_gridmodel->render(m_gridshader);
	m_gridshader.unbind();

	m_shader.bind();
	m_shader.setUniform("projectionMatrix", m_matrixStack.getProjectionMatrix());
	m_shader.setUniform("viewMatrix", m_matrixStack.getViewMatrix());
	m_shader.setUniform("screen_resolution", glm::vec2(m_display->getSrcWidth(), m_display->getSrcHeight()));
	m_light.bind(m_shader);
	for (psEntity *entity : m_entities) {
		entity->render(m_matrixStack, m_shader);
	}

	m_shader.unbind();

	m_buffer_loader.unbind();
	glDisable(GL_DEPTH_TEST);
	m_buffer_loader.process();

	m_display->refresh();
}

unsigned int psGameLoader::setup() {

	// In the case something goes wrong and GLEW is working on it's edge.
	if (m_display->initContext() & (INIT_MISMATCH | WINDOW_CREATION_FAIL))
		return 1;

	m_physics.setup_physics();
	m_shader.create();
	m_shader.setupVertexShader(readfile_s("resource/vertex.glsl"));
	m_shader.setupVertexShader(readfile_s("resource/global_vertex_functions.glsl"));
	m_shader.setupFragmentShader(readfile_s("resource/fragment.glsl"));
	m_shader.link();
	m_entitymodel = new psModel("resource/scene/obama/cube.obj");

	// Floor setup
	m_gridshader.create();
	m_gridshader.setupVertexShader(readfile_s("resource/grid_vertex.glsl"));
	m_gridshader.setupFragmentShader(readfile_s("resource/grid_fragment.glsl"));
	m_gridshader.link();
	m_gridmodel = new psModel("resource/scene/plane.obj");

	m_buffer_loader.load(m_display);

	return 0;
}

void psGameLoader::run() {

	float a{ 0.f };
	const float stepf{ 1.f / m_fps };
	const float stepu{ 1.f / m_ups };
	m_clock.setup();
	while (!m_display->shouldClose()) {
		//double temp = m_clock.getHook();
		a += m_clock.getSequence();
		while (a >= stepu) {
			//LOGICAL UPDATES HERE
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
				m_entities.push_back(new psEntity(glm::vec3(0.f, 15.f, 0.f), 10.f, m_entitymodel, m_physics));
			}

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			m_camera.setRotation(m_display->getViewPitch(), m_display->getViewYaw(), 0.f);
			m_camera.move(x, y, z);
			m_physics.update(a, m_matrixStack);
			for (psEntity *entity : m_entities) {
				entity->tick(m_physics);
			}

			a -= stepu;
		}

		//float last = (float)temp + stepf;
		//if (m_clock.getSystemTime() >= last)
		sub_render();

	}

}

void psGameLoader::terminate() {

	m_gridmodel->dispose();
	m_physics.dispose();
	for (psEntity *entity : m_entities) {
		delete entity;
	}

	m_entities.clear();
	m_gridshader.dispose();
	m_buffer_loader.dispose();
	m_shader.dispose();
	m_display->dispose();
}