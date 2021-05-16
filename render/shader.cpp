#include "shader.hpp"

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

void psShader::create() {

	program = glCreateProgram();
	// Not sure what to do here.
	// TODO: Error handling.
	if (!program)
		return;

	uniforms = genmap<const char *, int>(8, hash_chrp);
}

void psShader::buildUniform(const char *name) {

	int uniform = glGetUniformLocation(program, name);
	if (uniform < 0)
		return;

	putmap(uniforms, name, uniform);
}

void psShader::setUniform(const char *name, int value) {

	int uniform;
	getmap(uniforms, name, &uniform);
	glUniform1i(uniform, value);
}

void psShader::setUniform(const char *name, float value) {

	int uniform;
	getmap(uniforms, name, &uniform);
	glUniform1f(uniform, value);
}

void psShader::setUniform(const char *name, const vec3 &value) {
	
	int uniform;
	getmap(uniforms, name, &uniform);
	glUniform3fv(uniform, 1, &value[0]);
}

void psShader::setUniform(const char *name, const mat4 &value) {

	int uniform;
	getmap(uniforms, name, &uniform);
	glUniformMatrix4fv(uniform, 1, false, &value[0][0]);
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