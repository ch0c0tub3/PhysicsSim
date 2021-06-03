#version 460

in vec3 vertex;
out vec4 fragColor;

void main() {

	vec2 coord = vertex.xz;
	vec2 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
	float line = min(grid.x, grid.y);
	fragColor = vec4(vec3(1.0 - min(line, 1.0)), 1.0 - line);
}