#ifndef PS_MESH_PROTOTYPE
#define PS_MESH_PROTOTYPE

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "GL/glew.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>

struct psMeshData {

	glm::vec3 vertex;
	glm::vec2 uv;
	glm::vec3 normal;
	float texture_id;
};

class psMesh {

protected:

	unsigned int m_vao;
	size_t m_numVbos;
	unsigned int *m_vbos;
	size_t m_numIndices;

public:

	psMesh(std::vector<psMeshData> vertices, std::vector<unsigned int> indices);

	void render();

	void dispose();

};

#endif