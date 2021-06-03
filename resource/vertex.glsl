#version 460

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normalIn;
layout (location = 3) in float texture_id;

struct frag_info {

	vec3 camera;
	vec3 vertex;
	vec3 normal;
	vec2 uv;
	float tex_index;
};

out frag_info pass_data;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform vec2 screen_resolution;

vec4 snap_vertex(vec3 vertex, mat4 projectionMatrix, mat4 viewMatrix, mat4 modelMatrix, float grid);

void main() {

	// An average resolution for ancient graphics.
	// Simply 800 x 600 or 4 / 3.
	vec4 vertex = snap_vertex(position, projectionMatrix, viewMatrix, modelMatrix, min(screen_resolution.x, screen_resolution.y));
	gl_Position = projectionMatrix * vertex;

	// Send additional data to the fragment shader for computing values.
	pass_data.camera = (projectionMatrix * viewMatrix * vec4(1.0)).xyz;
	pass_data.vertex = vertex.xyz;
	pass_data.normal = normalIn;
	pass_data.uv = texCoord * vertex.z;
	pass_data.tex_index = texture_id;
}