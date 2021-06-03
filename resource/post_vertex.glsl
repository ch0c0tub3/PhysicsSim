#version 460

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 uv;

void main() {

	gl_Position = vec4(position, 0.0, 1.0);
	uv = texCoords;
}