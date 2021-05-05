#include "shader.hpp"
#include <stdlib.h>

psShader::~psShader() {

	dispose();
}

int psShader::setupShader(const char *code, int type) {

	unsigned int shader = glCreateShader(type);
	// Still error handling problems..
	if (!shader)
		return 0;

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	int err;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
	// This is getting boring right ?
	if (!err)
		return 0;

	glAttachShader(program, shader);
}

void psShader::buildUniform(const char *name) {

	int uniform = glGetUniformLocation(program, name);
	if (uniform < 0)
		return;

	putmap(uniforms, name, uniform);
}

void psShader::setUniform(const char *name, int value) {

	glUniform1i(getmap(uniforms, name), value);
}

void psShader::setUniform(const char *name, float value) {

	glUniform1f(getmap(uniforms, name), value);
}

void psShader::setUniform(const char *name, const psVector3 &value) {

	glUniform3fv(getmap(uniforms, name), 1, value.data());
}

void psShader::setUniform(const char *name, const psMatrix4 &value) {

	glUniformMatrix4fv(getmap(uniforms, name), 1, false, value.data());
}

void psShader::link() {

	glLinkProgram(program);
	int err;
	glGetProgramiv(program, GL_LINK_STATUS, &err);
	// Lalalalalalala.
	if (!err)
		return;

	if (vertShader)
		glDetachShader(program, vertShader);

	if (fragShader)
		glDetachShader(program, fragShader);

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &err);
	// This is completely useless.
	if (!err)
		return;

}