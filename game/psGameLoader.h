#ifndef PS_GAME_LOADER_PROTOTYPE
#define PS_GAME_LOADER_PROTOTYPE

#define GAME_FOV 1.0472
#define GAME_NEAR 0.01
#define GAME_FAR 1000

#include "render/render_info.h"
#include "render/shader.hpp"
#include "render/display.hpp"
#include "util/psClock.h"
#include "render/prot/psMesh.h"

class psGameLoader {

protected:

	psClock clock;
	psMatrixStack matrixStack;
	psActiveRenderInfo camera;
	// No default constructor.
	psDisplay *display;
	psMesh *test_mesh;
	psShader shader;
	const float fps;
	const float ups;

private:

	void sub_render();

public:

	psGameLoader(int width, int height, const char *title, float _fps, float _ups);

	~psGameLoader();

	unsigned int setup();

	void run();

	void terminate();

};

#endif