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
#include "render/prot/psTextureLoader.h"

class psGameLoader {

protected:

	psClock m_clock;
	psMatrixStack m_matrixStack;
	psActiveRenderInfo m_camera;
	psDisplay *m_display;
	psMesh *m_test_mesh;
	psShader m_shader;
	const float m_fps;
	const float m_ups;

private:

	void sub_render();

public:

	psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups);

	~psGameLoader();

	unsigned int setup();

	void run();

	void terminate();

};

#endif