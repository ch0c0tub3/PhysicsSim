#version 330

out vec4 fragColor;

uniform float r;
uniform float g;
uniform float b;

void main() {

	fragColor = vec4(r, g, b, 1.0);
}