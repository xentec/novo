#version 330 core

in GS_FS {
	vec4 color;
} fsIn;

out vec4 color;

void main()
{
	color = fsIn.color;
}
