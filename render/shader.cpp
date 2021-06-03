#include "shader.hpp"

int psShader::setupShader(const char *code, const int &type) {

	unsigned int shader = glCreateShader(type);
	// Still error handling problems..
	if(!shader)
	{
		std::cout << "ERROR::SHADER::NOT_CREATED" << std::endl;
		return 0;
	}

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	int err;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
	// This is getting boring right ?
	if(!err)
	{
		static char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		
		std::cout << "ERROR::SHADER::";

		switch(type)
		{
			case GL_VERTEX_SHADER:
				std::cout << "VERTEX";
				break;

			case GL_FRAGMENT_SHADER:
				std::cout << "FRAGMENT";
				break;

			default:
				break;
		}
		std::cout << "::COMPILE_ERROR\n" << infoLog << std::endl;

		return 0;
	}

	glAttachShader(m_program, shader);

	return shader;
}

void psShader::create() {

	m_program = glCreateProgram();
	// Not sure what to do here.
	// TODO: Error handling.
	if (!m_program)
		return;

}

void psShader::setUniform(const char *name, const int *values, size_t num) {

	int uniform = glGetUniformLocation(m_program, name);
	glUniform1iv(uniform, num, values);
}

void psShader::setUniform(const char *name, const float *values, size_t num) {

	int uniform = glGetUniformLocation(m_program, name);
	glUniform1fv(uniform, num, values);
}

void psShader::setUniform(const char *name, const glm::vec2 &values_first_elm, size_t num) {

	int uniform = glGetUniformLocation(m_program, name);
	glUniform2fv(uniform, num, glm::value_ptr(values_first_elm));
}

void psShader::setUniform(const char *name, const glm::vec3 &values_first_elm, size_t index) {

	int uniform = glGetUniformLocation(m_program, name);
	glUniform3fv(uniform, index, glm::value_ptr(values_first_elm));
}

void psShader::setUniform(const char *name, const glm::mat4 &values_first_elm, size_t index) {

	int uniform = glGetUniformLocation(m_program, name);
	glUniformMatrix4fv(uniform, index, false, glm::value_ptr(values_first_elm));
}

int psShader::getAttribute(const char *name) {

	return glGetAttribLocation(m_program, name);
}

void psShader::link() {

	int state;
	static char info_log[512];
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &state);
	// Lalalalalalala
	if (!state) {
		glGetProgramInfoLog(m_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
		return;
	}

	if (!m_vertShaders.empty()) {
		for (unsigned int vertShader : m_vertShaders) {
			glDetachShader(m_program, vertShader);
		}

		m_vertShaders.clear();
	}

	if (!m_fragShaders.empty()) {
		for (unsigned int fragShader : m_fragShaders) {
			glDetachShader(m_program, fragShader);
		}

		m_fragShaders.clear();
	}

	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &state);
	if (!state) {
		glGetProgramInfoLog(m_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::RECALÉ\n" << info_log << std::endl;
		// This is completely useless.
		return;
	}

}