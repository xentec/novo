#include "origin.h"

#include <vector>

static const std::vector<vec4> vertices = {
	{0,0,0,1},
	{1,0,0,1},
	{0,1,0,1},
	{0,0,1,1},
};

static const std::vector<vec4> colors = {
	{0,0,0,1},
	{1,0,0,1},
	{0,1,0,1},
	{0,0,1,1},
};

static const std::vector<u8> indices = {
	0,1,	0,2,	0,3,
};

Origin::Origin(f32 length, f32 width):
	Entity(vec3(0)), Drawable(),
	length(length), width(width)
{
	prog.setLabel("Origin");
	prog.attach(Shader::load(ShaderType::Vertex, "plain.v.glsl"));
	prog.attach(Shader::load(ShaderType::Fragment, "plain.f.glsl"));
	prog.use();

	prog.bindFragDataLocation(0, "color");

	vbo.allocateElements(BufferUsage::StaticDraw, vertices, colors);
	vao.addAttribute(vbo, vertices, prog.getAttribute("pos"), vertices[0].length(), DataType::Float);
	vao.addAttribute(vbo, colors, prog.getAttribute("color"), colors[0].length(), DataType::Float);

	ibo.setElements(BufferUsage::StaticDraw, indices);
}

void Origin::draw(mat4 *transform)
{
	vao.bind();
	ibo.bind();
	prog.setUniform("model", *transform * translate(scale(mat4(), vec3(length)), pos));
	glLineWidth(width);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, nullptr);
	glLineWidth(1.0);
}

