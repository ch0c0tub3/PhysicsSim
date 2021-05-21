#include "psMesh.h"

psMesh::psMesh(const float vertices[], const int indices[], const size_t &sizev) : m_numVertices(sizev) {

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	m_vbos = static_cast<unsigned int *>(calloc(2, sizeof(unsigned int)));
	if (!m_vbos)
		return;

	glGenBuffers(2, m_vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_numVertices * 3, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_numVertices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

psMesh::~psMesh() {

	dispose();
}

void psMesh::render() {

	// EXPERIMENTAL
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void psMesh::dispose() {

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	while (*m_vbos) glDeleteBuffers(1, &(*m_vbos++));
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vao);
}