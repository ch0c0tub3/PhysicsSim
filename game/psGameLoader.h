#ifndef PS_GAME_LOADER_PROTOTYPE
#define PS_GAME_LOADER_PROTOTYPE

#define GAME_FOV 1.0472
#define GAME_NEAR 0.01
#define GAME_FAR 1000

#include <reactphysics3d/reactphysics3d.h>
#include <vector>

#include "render/render_info.h"
#include "render/shader.hpp"
#include "render/display.hpp"
#include "util/psClock.h"
#include "util/psFileLoader.h"
#include "psEntity.hpp"

class psGameLoader {

protected:

	psClock m_clock;
	psActiveRenderInfo m_camera;
	psDisplay *m_display;
	
	psShader m_shader;
	psLightSource m_light;

	std::vector<psEntity*> m_arrEntity;
	rp3d::PhysicsCommon m_physicsCommon;
	rp3d::PhysicsWorld *m_world;

	rp3d::RigidBody *m_floor;
	rp3d::Collider *m_floorCollider;

	psModel *m_commonmodel;

	const float m_fps;
	const float m_ups;

	// FOR DEBUGGING
	psShader m_gridshader;
	psModel *m_gridmodel;

private:

	void sub_render();

public:
	psGameLoader(const int &width, const int &height, const char *title, const float &_fps, const float &_ups);

	unsigned int setup();

	void run();

	void terminate();
};

#endif