#include "psGameLoader.h"
#include "util/psFileLoader.h"

psGameLoader::psGameLoader(int width, int height, const char *title, float _fps, float _ups) : fps(_fps), ups(_ups) {

	display = new psDisplay(width, height, title);
}

psGameLoader::~psGameLoader() {

	terminate();
}

void psGameLoader::sub_render() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.bind();
	matrixStack.updateProjectionMatrix(GAME_FOV, display->getWidth(), display->getHeight(), GAME_NEAR, GAME_FAR);
	shader.setUniform("projectionMatrix", matrixStack.getProjectionMatrix());
	matrixStack.updateViewMatrix(camera);
	matrixStack.updateModelViewMatrix(vec3(1.f, 0.f, -4.f), vec3(), 1.f);
	shader.setUniform("modelViewMatrix", matrixStack.getModelViewMatrix());
	shader.setUniform("r", 1.f);
	shader.setUniform("g", 0.3f);
	shader.setUniform("b", 0.1f);
	test_mesh->render();
	shader.unbind();
	display->refresh();
}

unsigned int psGameLoader::setup() {

	// In the case something goes wrong and GLEW is working on it's edge.
	if (display->initContext() & (INIT_MISMATCH | WINDOW_CREATION_FAIL))
		return 1;

	shader.create();
	shader.setupVertexShader(readfile_s("resource/vertex.glsl"));
	shader.setupFragmentShader(readfile_s("resource/fragment.glsl"));
	shader.link();
	shader.buildUniform("projectionMatrix");
	shader.buildUniform("modelViewMatrix");
	shader.buildUniform("r");
	shader.buildUniform("g");
	shader.buildUniform("b");
	float vertices[] = {
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0
	};
	int indices[] = {
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
	test_mesh = new psMesh(vertices, indices, 20);

	return 0;
}

void psGameLoader::run() {

	float a = 0.f;
	float step = 1.f / ups;
	while (!display->shouldClose()) {
		a += clock.getSequence();
		while (a >= step) {
			//LOGICAL UPDATES HERE
			float x = 0.f, y = 0.f, z = 0.f;
			if (display->isKeyPressed(GLFW_KEY_SPACE)) {
				y += 0.05f;
			}

			if (display->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
				y -= 0.05f;
			}

			if (display->isKeyPressed(GLFW_KEY_W)) {
				z -= 0.05f;
			}

			if (display->isKeyPressed(GLFW_KEY_S)) {
				z += 0.05f;
			}

			if (display->isKeyPressed(GLFW_KEY_A)) {
				x -= 0.05f;
			}

			if (display->isKeyPressed(GLFW_KEY_D)) {
				x += 0.05f;
			}

			camera.rotate(display->getPitch() * 0.01f, display->getYaw() * 0.01f, 0.f);
			camera.move(x, y, z);
			a -= step;
		}

		sub_render();
	}

}

void psGameLoader::terminate() {

	test_mesh->dispose();
	shader.dispose();
	display->dispose();
}