#ifndef PS_SHADER_PROTOTYPE
#define PS_SHADER_PROTOTYPE

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "util/hash_map.h"
#include "util/hashfunc.h"

using namespace glm;

class psShader {

protected:

	unsigned int program;
	unsigned int vertShader;
	unsigned int fragShader;
	struct hmap_data<const char *, int> *uniforms;

	virtual int setupShader(const char *code, int type);

public:

	psShader() {}

	virtual ~psShader();

	virtual void create();

	virtual void buildUniform(const char *name);

	virtual void setUniform(const char *name, int value);

	virtual void setUniform(const char *name, float value);

	virtual void setUniform(const char *name, const vec3 &value);

	virtual void setUniform(const char *name, const mat4 &value);

	void setupVertexShader(const char *code) {

		vertShader = setupShader(code, GL_VERTEX_SHADER);
	}

	void setupFragmentShader(const char *code) {

		fragShader = setupShader(code, GL_FRAGMENT_SHADER);
	}

	virtual void link();

	void bind() {

		if (program)
			glUseProgram(program);

	}

	void unbind() {

		glUseProgram(0);
	}

	void dispose() {

		unbind();
		if (program)
			glDeleteProgram(program);

	}

};

#endif