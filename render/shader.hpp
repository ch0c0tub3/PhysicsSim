#ifndef PS_SHADER_PROTOTYPE
#define PS_SHADER_PROTOTYPE

#include <iostream>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "util/hash_map.h"
#include "util/hashfunc.h"

class psShader {

protected:

	unsigned int m_program;
	unsigned int m_vertShader;
	unsigned int m_fragShader;
	struct hmap_data<const char *, int> *m_uniforms;

	virtual int setupShader(const char *code, const int &type);

public:

	psShader() {}

	virtual void create();

	virtual void buildUniform(const char *name);

	virtual void setUniform(const char *name, const int &value);

	virtual void setUniform(const char *name, const float &value);

	virtual void setUniform(const char *name, const glm::vec2 &value);

	virtual void setUniform(const char *name, const glm::vec3 &value);

	virtual void setUniform(const char *name, const glm::mat4 &value);

	void setupVertexShader(const char *code) {

		m_vertShader = setupShader(code, GL_VERTEX_SHADER);
	}

	void setupFragmentShader(const char *code) {

		m_fragShader = setupShader(code, GL_FRAGMENT_SHADER);
	}

	virtual void link();

	void bind() {

		if (m_program)
			glUseProgram(m_program);

	}

	void unbind() {

		glUseProgram(0);
	}

	void dispose() {

		unbind();
		if (m_program)
			glDeleteProgram(m_program);

		freemap(m_uniforms);
	}

};

#endif