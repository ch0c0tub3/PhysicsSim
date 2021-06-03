#ifndef PS_GAME_LOADER_PROTOTYPE
#define PS_GAME_LOADER_PROTOTYPE


#define GAME_FOV 1.0472
#define GAME_NEAR 0.01
#define GAME_FAR 1000

#include <stdint.h>

#define MAX_ENTITIES USHRT_MAX

#include "render/render_info.h"
#include "render/shader.hpp"
#include "render/display.hpp"
#include "util/psClock.h"
#include "render/prot/psModel.h"
#include "render/prot/psLightSource.h"
#include "items/psPhysicsWorld.h"
#include "items/psEntity.h"
#include "render/prot/psPostProcessingLoader.h"

class psGameLoader {

protected:

	psClock m_clock;
	psMatrixStack m_matrixStack;
	psActiveRenderInfo m_camera;
	psDisplay *m_display;
	psShader m_shader;
	psLightSource m_light;
	psPhysicsWorld m_physics;
	std::vector<psEntity *> m_entities;
	psShader m_gridshader;
	psModel *m_gridmodel;
	psModel *m_entitymodel;
	psPostProcessingLoader m_buffer_loader;
	const float m_fps;
	const float m_ups;

private:

	void sub_render();

public:

	psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups);

	unsigned int setup();

	void run();

	void terminate();

};

#endif