#ifndef PS_SHADER_PROTOTYPE
#define PS_SHADER_PROTOTYPE

#include <GL/glew.h>
#include "util/math/psVector3.h"
#include "util/math/psMatrix4.h"
#include "util/hash_map.h"
#include "util/hashfunc.h"

class psShader {

protected:

	unsigned int program;
	unsigned int vertShader;
	unsigned int fragShader;
	struct hmap_data<const char *, int> *uniforms;

	virtual int setupShader(const char *code, int type);

public:

	psShader() {

		program = glCreateProgram();
		// Not sure what to do here.
		// TODO: Error handling.
		if (!program)
			return;

		uniforms = genmap<const char*, int>(5, hash_chrp);
	}

	virtual ~psShader();

	virtual void buildUniform(const char *name);

	virtual void setUniform(const char *name, int value);

	virtual void setUniform(const char *name, float value);

	virtual void setUniform(const char *name, const psVector3 &value);

	virtual void setUniform(const char *name, const psMatrix4 &value);

	void setupVertexShader(const char *code) {

		vertShader = setupShader(code, GL_FRAGMENT_SHADER);
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