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

	m_uniforms = genmap<const char *, int>(8, hash_chrp);
}

void psShader::buildUniform(const char *name) {

	int uniform = glGetUniformLocation(m_program, name);
	if (uniform < 0)
		return;

	putmap(m_uniforms, name, uniform);
}

void psShader::setUniform(const char *name, const int &value) {

	int uniform;
	getmap(m_uniforms, name, &uniform);
	glUniform1i(uniform, value);
}

void psShader::setUniform(const char *name, const float &value) {

	int uniform;
	getmap(m_uniforms, name, &uniform);
	glUniform1f(uniform, value);
}

void psShader::setUniform(const char *name, const glm::vec2 &value) {

	int uniform;
	getmap(m_uniforms, name, &uniform);
	glUniform2fv(uniform, 1, &value[0]);
}

void psShader::setUniform(const char *name, const glm::vec3 &value) {
	
	int uniform;
	getmap(m_uniforms, name, &uniform);
	glUniform3fv(uniform, 1, &value[0]);
}

void psShader::setUniform(const char *name, const glm::mat4 &value) {

	int uniform;
	getmap(m_uniforms, name, &uniform);
	glUniformMatrix4fv(uniform, 1, false, &value[0][0]);
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

	if (m_vertShader)
		glDetachShader(m_program, m_vertShader);

	if (m_fragShader)
		glDetachShader(m_program, m_fragShader);

	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &state);
	if (!state) {
		glGetProgramInfoLog(m_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::RECALÉ\n" << info_log << std::endl;
		// This is completely useless.
		return;
	}

}