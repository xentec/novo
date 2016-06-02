#version 330 core

layout(location = 0) in vec4 pos;

out VS_FS {
	vec4 color;
} vsOut;

uniform vec4 color;
uniform mat4 proj, view, model;

void main()
{
	vsOut.color = color;
	gl_Position = proj * view * model * pos;
}
