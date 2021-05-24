#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normalIn;

out vec3 normal;
out vec2 uv;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
	normal = normalIn;
	uv = texCoord;
}