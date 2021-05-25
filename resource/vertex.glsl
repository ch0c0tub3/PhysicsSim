#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normalIn;

out vec3 vnormal;
out vec3 vpos;
out vec2 uv;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {

	vec4 modelpos = viewMatrix * modelMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * modelpos;
	vnormal = normalize(viewMatrix * modelMatrix * vec4(normalIn, 0.0)).xyz;
	vpos = modelpos.xyz;
	uv = texCoord;
}