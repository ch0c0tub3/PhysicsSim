#version 460

vec4 snap_vertex(vec3 vertex, mat4 projectionMatrix, mat4 viewMatrix, mat4 modelMatrix, float grid) {

	vec3 snapped = (viewMatrix * modelMatrix * vec4(vertex, 1.0)).xyz;
	float z_origin = snapped.z;
	float i = 0.5 * grid / 2.0;
	float w = (projectionMatrix * vec4(snapped, 1.0)).w;
	snapped = round(snapped / w * i) / i * w;
	snapped.z = z_origin;

	return vec4(snapped, 1.0);
}