#version 330 core

in vec2 pos;
in vec2 tex;

out VS_FS {
	vec2 tex;
} vsOut;

void main() {
	vsOut.tex = tex;
	gl_Position = vec4(pos, 0.0, 1.0);
}
