#include "psMesh.h"

psMesh::psMesh(float vertices[], float normals[], int indices[], size_t size) {

	num_vertices = size;
	glGenVertexArrays(1, &vao);
	vbos = (unsigned int *)calloc(3, sizeof(unsigned int));
	glGenBuffers(1, &vbos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glGenBuffers(1, &vbos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	// ha bools
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, NULL);
	glGenBuffers(1, &vbos[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

psMesh::~psMesh() {

	dispose();
}

void psMesh::render() {

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void psMesh::dispose() {

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (*vbos) glDeleteBuffers(1, &(*vbos++));
	free(vbos);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
}