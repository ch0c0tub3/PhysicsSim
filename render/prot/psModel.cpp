#include "psModel.h"

psModel::psModel(const char *filename) {

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
		throw importer.GetErrorString();

	std::vector<psMesh> meshes;
	m_filesource = filename;
	m_filesource = m_filesource.substr(0, m_filesource.find_last_of('/') + 1);
	m_shape = new btConvexHullShape();
	if (scene->mRootNode)
		parse_meshes(scene->mRootNode, scene, meshes);

	m_numComponents = meshes.size();
	m_components = (psMesh *)calloc(m_numComponents, sizeof(psMesh));
	if (!m_components)
		return;

	for (size_t i = 0; i < m_numComponents; i++) {
		m_components[i] = meshes[i];
	}

	((btConvexHullShape *)m_shape)->optimizeConvexHull();
	((btConvexHullShape *)m_shape)->initializePolyhedralFeatures();
}

void psModel::gen_textures(aiMaterial *material, aiTextureType type, psTextureType alias) {

	for (size_t i = 0; i < material->GetTextureCount(type); i++) {

		aiString path;
		material->GetTexture(type, i, &path);
		std::string str = m_filesource + path.C_Str();
		const char *data = str.c_str();
		char *pass = new char[strlen(data) + 1];
		strcpy(pass, data);
		l_texturecache.load(pass, alias);
	}

}

psMesh psModel::create_mesh(aiMesh *aimesh, const aiScene *scene) {

	std::vector<psMeshData> vertices;
	std::vector<unsigned int> indices;
	for (size_t i = 0; i < aimesh->mNumVertices; i++) {
		aiVector3D vertex = aimesh->mVertices[i];
		psMeshData data;
		data.vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
		((btConvexHullShape *)m_shape)->addPoint(btVector3(vertex.x, vertex.y, vertex.z));
		if (aimesh->HasNormals()) {
			aiVector3D normal = aimesh->mNormals[i];
			data.normal = glm::vec3(normal.x, normal.y, normal.z);
		}

		if (aimesh->mTextureCoords[0]) {
			aiVector3D uv = aimesh->mTextureCoords[0][i];
			data.uv = glm::vec2(uv.x, 1.f - uv.y);
		}
		else {
			data.uv = glm::vec2(0.f, 0.f);
		}

		data.texture_id = (float)(aimesh->mMaterialIndex - 1);
		vertices.push_back(data);
	}

	for (size_t i = 0; i < aimesh->mNumFaces; i++) {
		aiFace face = aimesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}

	}

	aiMaterial *material = scene->mMaterials[aimesh->mMaterialIndex];
	gen_textures(material, aiTextureType_DIFFUSE, psTextureType::DIFFUSE);
	gen_textures(material, aiTextureType_SPECULAR, psTextureType::SPECULAR);
	gen_textures(material, aiTextureType_HEIGHT, psTextureType::NORMAL);
	gen_textures(material, aiTextureType_AMBIENT, psTextureType::HEIGHT);

	return psMesh(vertices, indices);
}

void psModel::render(psShader &shader) {

	l_texturecache.bind(shader);
	for (size_t i = 0; i < m_numComponents; i++) {
		m_components[i].render();
	}

	l_texturecache.unbind();
}

void psModel::addSpecialTexture(const char *path) {

	l_texturecache.load(path, psTextureType::SPECIAL);
}

btCollisionShape *psModel::get_btshape() {

	return m_shape;
}

void psModel::dispose() {

	for (size_t i = 0; i < m_numComponents; i++) {
		m_components[i].dispose();
	}

	free(m_components);
	m_numComponents = 0;
	l_texturecache.dispose();
}