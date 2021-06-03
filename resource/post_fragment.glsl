#version 460

in vec2 uv;
out vec4 fragColor;

uniform sampler2D texture_loc;

const float pattern[4] = float[4](
	0.25, 0.75,
	1.00, 0.50
);

vec3 gaussian_blur(sampler2D texture_src, vec2 macro_uv) {

	float offset = 0.003;
	vec4 oc = texture(texture_src, macro_uv);
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0, offset),
		vec2(offset, offset),
		vec2(-offset, 0.0),
		vec2(0.0, 0.0),
		vec2(offset, 0.0),
		vec2(-offset, -offset),
		vec2(0.0, -offset),
		vec2(offset, -offset)
	);
	float kernel[9] = float[](
		0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625
	);
	vec3 color = vec3(0.0);
	vec3 samples[9];
	for (int i = 0; i < 9; i++) {
		samples[i] = vec3(texture(texture_src, macro_uv.st + offsets[i]));
		color += samples[i] * kernel[i];
	}

	return color;
}

float luma(vec3 tint) {

	return dot(tint, vec3(0.299, 0.587, 0.114));
}

float luma(vec4 tint) {

	return luma(tint.rgb);
}

float dither(vec2 frag, float brightness) {
	
	int x = int(mod(frag.x, 2.0));
	int y = int(mod(frag.y, 2.0));
	float limit = 0.0;
	if (x < 8)
		limit = pattern[x + y * 2];

	return brightness < limit ? 0.2 : 1.0;
}

void main() {

	vec4 tint = texture(texture_loc, uv);
	fragColor = vec4(tint.rgb * dither(gl_FragCoord.xy, luma(tint)), 1.0);
}