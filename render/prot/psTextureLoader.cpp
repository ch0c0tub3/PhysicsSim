#include "psTextureLoader.h"

psTextureLoader::~psTextureLoader() {

	dispose();
}

void psTextureLoader::load(const char *filename, const char *name) {

	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
	if (!data)
		return;

	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	putmap(identities, name, id);
}

void psTextureLoader::bind(const char *name) {

	unsigned int id;
	getmap(identities, name, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

void psTextureLoader::unbind() {

	glBindTexture(GL_TEXTURE_2D, 0);
}

void psTextureLoader::dispose() {

	for (size_t i = 0; i < identities->size; i++) {
		struct hmap_data_node<const char *, unsigned int> *ptr = identities->data[i];
		while (ptr) {
			glDeleteTextures(1, &ptr->value);
			ptr = ptr->next;
		}

	}

	freemap(identities);
}