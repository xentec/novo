#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 12) out;

in VS_GS {
	vec4 norm;
} gsIn[];

out GS_FS {
	vec4 color;
} gsOut;

uniform mat4 proj, view, model;


void main()
{
	mat4 M = proj * view * model;
/*/
	vec3 a = gl_in[0].gl_Position.xyz,
		 b = gl_in[1].gl_Position.xyz,
		 c = gl_in[2].gl_Position.xyz;


	vec4 normal = vec4(normalize(cross(b-a, c-a)), 0.0);
	vec4 tri_centroid = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;

	gsOut.color = vec4(0,1,1,1);
	for(int i = 0; i<3; i++)
	{
		gl_Position = M * gl_in[i].gl_Position;
		EmitVertex();

		gl_Position = M * (gl_in[i].gl_Position + normal);
		EmitVertex();
		EndPrimitive();
	}
//*/
	gsOut.color = vec4(1,1,0,1);
	for(int i = 0; i<3; i++)
	{
		vec4 vNormal = gsIn[i].norm;

		gl_Position = M * gl_in[i].gl_Position;
		EmitVertex();

		gl_Position = M * (gl_in[i].gl_Position + vec4(vNormal.xyz, 0));
		EmitVertex();
		EndPrimitive();
	}
}
