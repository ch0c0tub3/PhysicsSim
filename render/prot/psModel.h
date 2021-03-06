#ifndef PS_MODEL_PROTOTYPE
#define PS_MODEL_PROTOTYPE

#include "render/shader.hpp"
#include "psMesh.h"
#include "psTextureLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include <reactphysics3d/reactphysics3d.h>

typedef struct {

	size_t num_vertices;
	float *vertices;
	int v_stride;
	unsigned int *indices;
	int i_stride;
	size_t num_faces;
	rp3d::PolygonVertexArray::PolygonFace *faces;
	rp3d::PolygonVertexArray::VertexDataType vertex_type;
	rp3d::PolygonVertexArray::IndexDataType index_type;
} rp3d_manifold;

class psModel {

protected:

	psTextureLoader m_texturecache;
	psMesh *m_components;
	size_t m_numComponents;
	std::string m_filesource;

	psMesh create_mesh(aiMesh *aimesh, const aiScene *scene);

	void gen_textures(aiMaterial *material, aiTextureType type, psTextureType alias);

	void parse_meshes(aiNode *src, const aiScene *scene, std::vector<psMesh> &dest) {

		for (size_t i = 0; i < src->mNumMeshes; i++) {
			aiMesh *aimesh = scene->mMeshes[src->mMeshes[i]];
			dest.push_back(create_mesh(aimesh, scene));
		}

		for (size_t i = 0; i < src->mNumChildren; i++) {
			parse_meshes(src->mChildren[i], scene, dest);
		}

	}

public:

	psModel(const char *filename);

	void render(psShader &shader);

	void addSpecialTexture(const char *path);

	void dispose();

};

#endif