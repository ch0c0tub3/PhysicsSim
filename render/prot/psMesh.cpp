#include "psMesh.h"

psMesh::psMesh(float vertices[], int indices[], size_t sizev) {

	num_vertices = sizev;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vbos = (unsigned int *)calloc(2, sizeof(unsigned int));
	if (!vbos)
		return;

	glGenBuffers(2, vbos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_vertices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

psMesh::~psMesh() {

	dispose();
}

void psMesh::render() {

	// EXPERIMENTAL
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void psMesh::dispose() {

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (*vbos) glDeleteBuffers(1, &(*vbos++));
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
}