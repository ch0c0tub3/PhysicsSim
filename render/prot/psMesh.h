#ifndef PS_MESH_PROTOTYPE
#define PS_MESH_PROTOTYPE

#include "GL/glew.h"
#include "util/math/psVector3.h"
#include <stdlib.h>
#include <vector>

#pragma warning(push)
#pragma warning(disable : 6386)

class psMesh {

protected:

	unsigned int m_vao;
	unsigned int *m_vbos;
	size_t m_numVertices;

public:

	psMesh(const float vertices[], const int indices[], const size_t &sizev);

	~psMesh();

	void render();

	void dispose();

};

#pragma warning(pop)

#endif