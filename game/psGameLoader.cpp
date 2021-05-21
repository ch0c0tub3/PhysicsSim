#include "psGameLoader.h"
#include "util/psFileLoader.h"

psGameLoader::psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups) : m_fps(_fps), m_ups(_ups), m_display(new psDisplay(width, height, title)) {

}

psGameLoader::~psGameLoader() {

	terminate();
}

void psGameLoader::sub_render() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader.bind();
	m_matrixStack.updateProjectionMatrix(GAME_FOV, m_display->getWidth(), m_display->getHeight(), GAME_NEAR, GAME_FAR);
	m_shader.setUniform("projectionMatrix", m_matrixStack.getProjectionMatrix());
	m_matrixStack.updateViewMatrix(m_camera);
	m_matrixStack.updateModelMatrix(glm::vec3(1.f, 0.f, -4.f), glm::vec3(), 1.f);
	m_shader.setUniform("modelMatrix", m_matrixStack.getModelMatrix());
	m_shader.setUniform("viewMatrix", m_matrixStack.getViewMatrix());
	m_shader.setUniform("r", 1.f);
	m_shader.setUniform("g", 0.3f);
	m_shader.setUniform("b", 0.1f);
	m_test_mesh->render();
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
	m_shader.buildUniform("r");
	m_shader.buildUniform("g");
	m_shader.buildUniform("b");
	constexpr float vertices[] = {
		-1.f, -1.f,  1.f,
		1.f, -1.f,  1.f,
		1.f,  1.f,  1.f,
		-1.f,  1.f,  1.f,
		-1.f, -1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
		1.f, -1.f, -1.f,
		1.f, -1.f, -1.f,
		1.f, -1.f, 1.f,
		1.f, -1.f, 1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, -1.f,
		-1.f, -1.f, 1.f,
		-1.f, -1.f, 1.f,
		1.f, 1.f, 1.f,
		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, 1.f, -1.f,
		-1.f, 1.f, -1.f
	};
	constexpr int indices[] = {
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};
	m_test_mesh = new psMesh(vertices, indices, 20);

	return 0;
}

void psGameLoader::run() {

	float a{0.f};
	float step{1.f / m_ups};
	while (!m_display->shouldClose()) {
		a += m_clock.getSequence();
		while (a >= step) {
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

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			m_camera.setRotation(m_display->getViewPitch(), m_display->getViewYaw(), 0.f);
			m_camera.move(x, y, z);
			a -= step;
		}

		sub_render();
	}

}

void psGameLoader::terminate() {

	m_test_mesh->dispose();
	m_shader.dispose();
	m_display->dispose();
}