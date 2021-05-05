#ifndef PS_MESH_PROTOTYPE
#define PS_MESH_PROTOTYPE

#include "GL/glew.h"
#include "util/math/psVector3.h"
#include "util/psFileLoader.h"
#include <stdlib.h>

#pragma warning(push)
#pragma warning(disable : 6386)

class psMesh {

protected:

	unsigned int vao;
	unsigned int *vbos;
	size_t num_vertices;

public:

	psMesh(float vertices[], float normals[], int indices[], size_t size);

	// TODO Parse mesh from obj.
	static psMesh _from_obj(const char *filepath) {

		std::vector<psVector3> vertices;
		std::vector<psVector3> normals;
		union face {
			int components[3][3];
		};
		std::vector<face> faces;
		size_t size;
		const char **lines = readfile_to_lines(filepath, &size);
		for (size_t i = 0; i < size; i++) {
			char *line = (char *)trim_str(lines[i]);
			if (!sizeof(line) || line[0] == '#')
				continue;

			char *token = strtok(line, "\\s+");
			// No textures.
			// If the current line indicates a vertex.
			if (token == "v") {
				vertices.push_back(psVector3(
					(float)strtod(strtok(NULL, "\\s+"), NULL),
					(float)strtod(strtok(NULL, "\\s+"), NULL),
					(float)strtod(strtok(NULL, "\\s+"), NULL)
				));
			}
			// If the current line indicates a normal.
			else if (token == "vn") {
				normals.push_back(psVector3(
					(float)strtod(strtok(NULL, "\\s+"), NULL),
					(float)strtod(strtok(NULL, "\\s+"), NULL),
					(float)strtod(strtok(NULL, "\\s+"), NULL)
				));
			}
			// If the current line indicates a face.
			else if (token == "f") {
				face f;
				for (size_t j = 0; j < 3; j++) {
					token = strtok(NULL, "\\s+");
					char *split = strtok(token, "/");
					for (size_t k = 0; k < 3; k++) {
						f.components[j][k] = (int)strtod(strtok(NULL, "/"), NULL) - 1;
					}
				}
				faces.push_back(f);
			}
		}

		int *indices = new int[faces.size() * 3];
		float *positions = new float[vertices.size() * 3];
		for (size_t i = 0; i < vertices.size(); i++) {
			psVector3 vertex = vertices.at(i);
			positions[i * 3] = vertex.x();
			positions[i * 3 + 1] = vertex.y();
			positions[i * 3 + 2] = vertex.z();
		}

		float *norms = new float[normals.size() * 3];
		for (size_t i = 0; i < faces.size(); i++) {
			face f = faces.at(i);
			for (size_t j = 0; j < 3; j++) {
				int *idx = f.components[j];
				indices[i + j] = idx[0];
				psVector3 normal = normals.at(idx[2]);
				norms[idx[0] * 3] = normal.x();
				norms[idx[0] * 3 + 1] = normal.y();
				norms[idx[0] * 3 + 2] = normal.z();
			}
		}

		return psMesh(positions, norms, indices, faces.size() * 3);
	}

	~psMesh();

	void render();

	void dispose();

};

#pragma warning(pop)

#endif