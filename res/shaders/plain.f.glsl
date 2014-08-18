#version 150 core

in VS_FS {
	vec4 color;
} fs_in;

out vec4 color;

void main() {
	color = fs_in.color;
}
