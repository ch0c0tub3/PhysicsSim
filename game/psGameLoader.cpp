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
	matrixStack.updateModelMatrix(vec3(), vec3(), 1.f);
	shader.setUniform("modelMatrix", matrixStack.getModelMatrix());
	shader.setUniform("viewMatrix", matrixStack.getViewMatrix());
	shader.setUniform("texture_sampler", 0);
	textures.bind("default");
	test_mesh->render();
	textures.unbind();
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
	shader.buildUniform("modelMatrix");
	shader.buildUniform("viewMatrix");
	shader.buildUniform("texture_sampler");
	textures.load("resource/square.png", "default");
	float vertices[] = {
		1.f, -1.f, -1.f,
		1.f, -1.f, 1.f,
		-1.f, -1.f, 1.f,
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
	int indices[] = {
		10, 16, 12,
		23, 21, 19,
		14, 18, 11,
		5, 20, 17,
		2, 6, 22,
		0, 3, 7,
		8, 10, 12,
		15, 23, 19,
		9, 14, 11,
		1, 5, 17,
		13, 2, 22,
		4, 0, 7
	};
	test_mesh = new psMesh(vertices, indices, 36);

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

			// Direct movement, for smooth camera prefer <camera.rotate(_x,_y_z)>
			camera.setRotation(display->getViewPitch(), display->getViewYaw(), 0.f);
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