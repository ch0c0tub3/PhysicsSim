#include "psTextureLoader.h"

void psTextureLoader::load(const char *filename, psTextureType textureType) {

	if (containsmap(identities, filename, std::strcmp))
		return;

	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
	if (!data)
		return;

	texture tex;
	glGenTextures(1, &tex.id);
	glBindTexture(GL_TEXTURE_2D, tex.id);
	// From khronos hints.
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	tex.type = textureType;
	putmap(identities, filename, tex);
}

void psTextureLoader::bind(psShader &shader) {

	unsigned int dc = 1;
	unsigned int ds = 1;
	unsigned int dn = 1;
	unsigned int dh = 1;
	unsigned int dd = 1;
	unsigned int ds0 = 1;
	int num = 0;
	for (size_t i = 0; i < identities->size; i++) {
		struct hmap_data_node<const char *, texture> *ptr = identities->data[i];
		while (ptr) {
			glActiveTexture(GL_TEXTURE0 + num);
			std::string name;
			switch (ptr->value.type) {
			case psTextureType::DIFFUSE:
				name = "texture_diffuse" + std::to_string(dc++);
				break;

			case psTextureType::SPECULAR:
				name = "texture_specular" + std::to_string(ds++);
				break;

			case psTextureType::NORMAL:
				name = "texture_normal" + std::to_string(dn++);
				break;

			case psTextureType::HEIGHT:
				name = "texture_height" + std::to_string(dh++);
				break;

			case psTextureType::SPECIAL:
				name = "texture_special" + std::to_string(ds0++);
				break;

			default:
				name = "texture_default" + std::to_string(dd++);
				break;

			}

			shader.setUniform(name.c_str(), num++);
			glBindTexture(GL_TEXTURE_2D, ptr->value.id);
			ptr = ptr->next;
		}

	}

}

void psTextureLoader::unbind() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void psTextureLoader::dispose() {

	auto _textureconsumer = [](void *ptr) {

		glDeleteTextures(1, &((texture *)ptr)->id);
	};
	freemap(identities, _textureconsumer);
}