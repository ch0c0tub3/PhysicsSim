#ifndef PS_SHADER_PROTOTYPE
#define PS_SHADER_PROTOTYPE

#include <iostream>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class psShader {

protected:

	unsigned int m_program;
	std::vector<unsigned int> m_vertShaders;
	std::vector<unsigned int> m_fragShaders;

	virtual int setupShader(const char *code, const int &type);

public:

	psShader() {

	}

	virtual void create();

	virtual void setUniform(const char *name, const int *values, size_t num);

	void setUniform(const char *name, const int &value) {

		setUniform(name, &value, 1);
	}

	virtual void setUniform(const char *name, const float *values, size_t num);

	void setUniform(const char *name, const float &value) {

		setUniform(name, &value, 1);
	}

	virtual void setUniform(const char *name, const glm::vec2 &values_first_elm, size_t num);

	void setUniform(const char *name, const glm::vec2 &value) {

		setUniform(name, value, 1);
	}

	virtual void setUniform(const char *name, const glm::vec3 &values_first_elm, size_t num);

	void setUniform(const char *name, const glm::vec3 &value) {

		setUniform(name, value, 1);
	}

	virtual void setUniform(const char *name, const glm::mat4 &values_first_elm, size_t num);

	void setUniform(const char *name, const glm::mat4 &value) {

		setUniform(name, value, 1);
	}

	virtual int getAttribute(const char *name);

	void setupVertexShader(const char *code) {

		m_vertShaders.push_back(setupShader(code, GL_VERTEX_SHADER));
	}

	void setupFragmentShader(const char *code) {

		m_fragShaders.push_back(setupShader(code, GL_FRAGMENT_SHADER));
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

	}

};

#endif