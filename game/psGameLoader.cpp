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
	matrixStack.updateModelViewMatrix(vec3(), vec3(), 1.f);
	shader.setUniform("modelViewMatrix", matrixStack.getModelViewMatrix());
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
	float vertices[] = {
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f
	};
	int indices[] = {
		0, 1, 3, 3, 1, 2,
		8, 10, 11, 9, 8, 11,
		12, 13, 7, 5, 12, 7,
		14, 15, 6, 4, 14, 6,
		16, 18, 19, 17, 16, 19,
		4, 6, 7, 5, 4, 7
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