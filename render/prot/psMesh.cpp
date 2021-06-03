#include "psMesh.h"

psMesh::psMesh(std::vector<psMeshData> vertices, std::vector<unsigned int> indices) : m_numIndices(indices.size()), m_numVbos(2) {

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	m_vbos = new unsigned int[m_numVbos];
	glGenBuffers(m_numVbos, m_vbos);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(psMeshData), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(psMeshData), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(psMeshData), (void *)offsetof(psMeshData, uv));
	// if you find any use of normals in a shader, apart from lights..
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(psMeshData), (void *)offsetof(psMeshData, normal));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(psMeshData), (void *)offsetof(psMeshData, texture_id));
	glBindVertexArray(0);
}

void psMesh::render() {

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void psMesh::dispose() {

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(m_numVbos, m_vbos);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vao);
	delete m_vbos;
}