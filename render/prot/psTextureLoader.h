#ifndef PS_TEXTURE_LOADER_PROTOTYPE
#define PS_TEXTURE_LOADER_PROTOTYPE

#include "GL/glew.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "util/hash_map.h"
#include "util/hashfunc.h"
#include "render/shader.hpp"
#include <string>

enum class psTextureType {

	NONE,
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT,
	SPECIAL
};

typedef struct {

	unsigned int id;
	psTextureType type;
} texture;

class psTextureLoader {

protected:

	struct hmap_data<const char *, texture> *identities
		= genmap<const char *, texture>(2, hash_chrp);

public:

	void load(const char *filename, psTextureType textureType);

	void bind(psShader &shader);

	void unbind();

	void dispose();

};

#endif