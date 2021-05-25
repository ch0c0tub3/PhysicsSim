#include "psGameLoader.h"
#include "util/psFileLoader.h"

psGameLoader::psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups) : m_fps(_fps), m_ups(_ups),
m_display(new psDisplay(width, height, title)), m_light(psLightSource(glm::vec3(1.f, 3.f, 4.f), glm::vec3(1.f, 0.9f, 0.87f), 1.f)) {

}

void psGameLoader::sub_render() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader.bind();
	m_matrixStack.updateProjectionMatrix(GAME_FOV, m_display->getWidth(), m_display->getHeight(), GAME_NEAR, GAME_FAR);
	m_shader.setUniform("projectionMatrix", m_matrixStack.getProjectionMatrix());
	m_matrixStack.updateViewMatrix(m_camera);
	m_matrixStack.updateModelMatrix(glm::vec3(1.f, 0.f, -4.f), glm::vec3(), 0.01f);
	m_shader.setUniform("modelMatrix", m_matrixStack.getModelMatrix());
	m_shader.setUniform("viewMatrix", m_matrixStack.getViewMatrix());
	m_light.bind(m_shader);
	m_test_model->render(m_shader);
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
	m_test_model = new psModel("resource/scene/Crysler_new_yorker_1980.obj");

	return 0;
}

void psGameLoader::run() {

	float a{0.f};
	float stepf{1.f / m_fps};
	float stepu{1.f / m_ups};
	while (!m_display->shouldClose()) {
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

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			m_camera.setRotation(m_display->getViewPitch(), m_display->getViewYaw(), 0.f);
			m_camera.move(x, y, z);
			a -= stepu;
		}

		//float last = m_clock.getHook() + stepf;
		//if(m_clock.getSystemTime() >= last)
			sub_render();

	}

}

void psGameLoader::terminate() {

	m_test_model->dispose();
	m_shader.dispose();
	m_display->dispose();
}