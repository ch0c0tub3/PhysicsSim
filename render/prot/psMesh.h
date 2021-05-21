#ifndef PS_MESH_PROTOTYPE
#define PS_MESH_PROTOTYPE

#include "GL/glew.h"
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

using namespace glm;

class psMesh {

private:

	static void split_str(std::string &res, const char &del, std::vector<std::string> &dest) {

		std::stringstream stream(res);
		std::string buf;
		while (std::getline(stream, buf, del)) {
			if (buf.length() > 0)
				dest.push_back(buf);

		}

	}

	static void trim_str(std::string &res) {

		res.erase(res.begin(), std::find_if(res.begin(), res.end(), [](unsigned char c) {
			return !std::isspace(c);
			}));
		res.erase(std::find_if(res.rbegin(), res.rend(), [](unsigned char c) {
			return !std::isspace(c);
			}).base(), res.end());
	}

	static vec3 &parse_vec3(std::vector<std::string> &tokens) {

		vec3 out;
		for (size_t i = 1; i < tokens.size(); i++) {
			if (i >= 4)
				break;

			out[i - 1] = std::stof(tokens[i]);
		}

		return out;
	}

	static vec2 &parse_vec2(std::vector<std::string> &tokens) {

		vec2 out;
		for (size_t i = 1; i < tokens.size(); i++) {
			if (i >= 3)
				break;

			out[i - 1] = std::stof(tokens[i]);
		}

		return out;
	}

	// Bi-dimensional array with dimensions 3 x 3
	static int **parse_face(std::vector<std::string> &tokens) {

		int **face = new int *[3];
		for (size_t i = 1; i < tokens.size(); i++) {
			if (i >= 4)
				break;

			face[i - 1] = new int[3];
			std::vector<std::string> split;
			split_str(tokens[i], '/', split);
			for (size_t j = 0; j < split.size(); j++) {
				if (j >= 3)
					break;

				face[i - 1][j] = std::stoi(split[j]) - 1;
			}

		}

		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				printf("%d/", face[i][j]);
			}

			printf("\n");
		}

		return face;
	}

	static psMesh send_to_mesh(std::vector<vec3> &vertices, std::vector<vec2> &uvs, std::vector<vec3> &normals, std::vector<int **> &faces) {

		int *indices = new int[faces.size() * 3];
		float *positions = new float[vertices.size() * 3];
		for (size_t i = 0; i < vertices.size(); i++) {
			vec3 vertex = vertices[i];
			positions[i * 3] = vertex.x;
			positions[i * 3 + 1] = vertex.y;
			positions[i * 3 + 2] = vertex.z;
		}

		float *textures = new float[vertices.size() * 2];
		float *norms = new float[vertices.size() * 3];
		for (size_t i = 0; i < faces.size(); i++) {
			for (size_t j = 0; j < 3; j++) {
				int *idx = faces[i][j];
				indices[i + j] = idx[0];
				vec2 uv = uvs[idx[1]];
				textures[idx[0] * 2] = uv.x;
				textures[idx[0] * 2 + 1] = 1.f - uv.y;
				vec3 normal = normals[idx[2]];
				norms[idx[0] * 3] = normal.x;
				norms[idx[0] * 3 + 1] = normal.y;
				norms[idx[0] * 3 + 2] = normal.z;
			}

		}

		return psMesh(positions, textures, norms, indices, vertices.size());
	}

protected:

	unsigned int vao;
	unsigned int *vbos;
	size_t num_vertices;

public:

	psMesh(float vertices[], int indices[], size_t sizev);

	psMesh(float vertices[], float uvs[], float normals[], int indices[], size_t sizev);

	static psMesh from_obj(const char *filename) {

		std::ifstream file(filename);
		if (!file.is_open()) {
			printf("Error occured loading file: %s\n", filename);
			throw "Couldn't open stream for file";
		}

		std::vector<vec3> vertices;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		std::vector<int **> faces;
		std::string line;
		while (std::getline(file, line)) {
			trim_str(line);
			if (line.empty() || !line.find("#"))
				continue;

			std::vector<std::string> tokens;
			split_str(line, ' ', tokens);
			if (tokens[0] == "v")
				vertices.push_back(parse_vec3(tokens));

			else if (tokens[0] == "vt")
				uvs.push_back(parse_vec2(tokens));

			else if (tokens[0] == "vn")
				normals.push_back(parse_vec3(tokens));

			else if (tokens[0] == "f")
				faces.push_back(parse_face(tokens));

		}

		return send_to_mesh(vertices, uvs, normals, faces);
	}

	~psMesh();

	void render();

	void dispose();

};

#endif