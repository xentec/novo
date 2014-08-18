#version 150 core

in vec4 pos;
in vec4 color;

out VS_FS {
	vec4 color;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

//uniform vec4 tex;

void main() {
	mat4 M = proj * view * model;
	vs_out.color = color;
	gl_Position = M * pos;
}
