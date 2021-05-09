#include "psGameLoader.h"
#include "util/psFileLoader.h"

psGameLoader::psGameLoader(int width, int height, const char *title, float _fps, float _ups) : fps(_fps), ups(_ups) {

	display = &psDisplay(width, height, title);
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
	matrixStack.updateModelViewMatrix(psVector3(0.f, 0.f, 10.f), psVector3(), 1.f);
	shader.setUniform("modelViewMatrix", matrixStack.getModelViewMatrix());
	shader.setUniform("color", psVector3(0.f, 1.f, 0.3f));
	shader.unbind();
	display->refresh();
}

unsigned int psGameLoader::setup() {

	// In the case something goes wrong and GLEW is working on it's edge.
	if (display->initContext() & (INIT_MISMATCH | WINDOW_CREATION_FAIL))
		return 1;

	shader.setupVertexShader(readfile_s("resource/vertex.glsl"));
	shader.setupFragmentShader(readfile_s("resource/fragment.glsl"));
	shader.link();
	shader.buildUniform("projectionMatrix");
	shader.buildUniform("modelViewMatrix");
	shader.buildUniform("color");

	return 0;
}

void psGameLoader::run() {

	float a = 0.f;
	float step = 1.f / ups;
	while (!display->shouldClose()) {
		a += clock.getSequence();
		while (a >= step) {
			/* LOGICAL UPDATES HERE */
			a -= step;
		}

		sub_render();
	}

}

void psGameLoader::terminate() {

	shader.dispose();
	display->dispose();
}