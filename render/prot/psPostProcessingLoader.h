#ifndef PS_POST_PROCESSING_LOADER_PROTOTYPE
#define PS_POST_PROCESSING_LOADER_PROTOTYPE

#include "GL/glew.h"
#include "render/shader.hpp"
#include "util/psFileLoader.h"
#include "render/display.hpp"
#include "render/render_info.h"

static constexpr float quads[] = {
	-1.f, 1.f, 0.f, 1.f,
	-1.f, -1.f, 0.f, 0.f,
	1.f, -1.f, 1.f, 0.f,
	-1.f, 1.f, 0.f, 1.f,
	1.f, -1.f, 1.f, 0.f,
	1.f, 1.f, 1.f, 1.f
};

class psPostProcessingLoader {

protected:
	
	psShader m_shader;
	unsigned int m_fbo;
	unsigned int m_texture;
	unsigned int m_rboDepth;
	unsigned int m_vbo, m_vao;
	psDisplay *m_display;
	int m_memwidth;
	int m_memheight;

public:

	psPostProcessingLoader() {

	}

	void load(psDisplay *display);

	void rescale();

	void bind();

	void unbind();

	void process();

	void dispose();

};

#endif