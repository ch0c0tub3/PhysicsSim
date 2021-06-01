#version 330

in vec3 vnormal;
in vec3 vpos;
in vec2 uv;

out vec4 fragColor;

uniform vec3 light_pos;
uniform vec3 light_tint;
uniform float light_power;
uniform sampler2D texture_diffuse1;

vec4 process_light(vec4 overlay) {

	float diff = max(dot(vnormal, normalize(light_pos - vpos)), 0.0);
	return overlay * vec4(light_tint, 1.0) * light_power * diff;
}

void main() {

	fragColor = process_light(texture(texture_diffuse1, uv));
	fragColor.a = 1.0;
}