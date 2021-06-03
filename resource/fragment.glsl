#version 460

struct frag_info {

	vec3 camera;
	vec3 vertex;
	vec3 normal;
	vec2 uv;
	float tex_index;
};

in frag_info pass_data;

out vec4 fragColor;

uniform vec3 light_pos;
uniform vec3 light_tint;
uniform float light_power;
uniform sampler2D texture_diffuse0;

vec4 process_light(vec4 overlay) {

	float diff = max(dot(pass_data.normal, normalize(light_pos - pass_data.vertex)), 0.0);
	return overlay * vec4(light_tint, 1.0) * light_power * diff;
}

float getFogAmount(float dist) {

	if (dist >= 200.0)
		return 1.0;

	else if (dist <= 80.0)
		return 0.0;

	return 1.0 - (200.0 - dist) / 120.0;
}

void main() {

	vec2 macro = pass_data.uv / pass_data.vertex.z;
	vec4 modtint = texture(texture_diffuse0, macro);
	float alpha = getFogAmount(distance(pass_data.camera, pass_data.vertex));
	if (alpha > 0.9)
		fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	
	else
		fragColor = mix(modtint, vec4(0.584, 0.592, 0.592, 1.0), alpha);

}