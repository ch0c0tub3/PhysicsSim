#version 330

in vec2 uv;
in vec3 normal;
out vec4 fragColor;

uniform vec3 lightdir;
uniform sampler2D texture_special1;

void main() {

	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec4 color = vec4(1.0, 0.9, 0.5, 1.0);
	float cl = clamp(-dot(normalize(lightdir), normalize(normal)), 0, 1);
	fragColor = texture(texture_special1, uv) * clamp(color * cl + ambient, 0, 1);
}