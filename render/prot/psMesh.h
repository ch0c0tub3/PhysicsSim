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

	unsigned int vao;
	unsigned int *vbos;
	size_t num_vertices;

public:

	psMesh(float vertices[], int indices[], size_t sizev);

	~psMesh();

	void render();

	void dispose();

};

#pragma warning(pop)

#endif