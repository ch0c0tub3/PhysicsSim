#ifndef PS_TEXTURE_LOADER_PROTOTYPE
#define PS_TEXTURE_LOADER_PROTOTYPE

#include "GL/glew.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "util/hash_map.h"
#include "util/hashfunc.h"

class psTextureLoader {

protected:

	struct hmap_data<const char *, unsigned int> *identities
		= genmap<const char *, unsigned int>(8, hash_chrp);

public:

	~psTextureLoader();

	void load(const char *filename, const char *name);

	void bind(const char *name);

	void unbind();

	void dispose();

};

#endif