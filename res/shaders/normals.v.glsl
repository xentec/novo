#version 330 core

in vec4 pos;
in vec4 norm;

out VS_GS {
	vec4 norm;
} vsOut;

void main()
{
	vsOut.norm = norm;
	gl_Position = pos;
}

