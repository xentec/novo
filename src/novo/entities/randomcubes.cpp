#include "randomcubes.h"

#include <novo/util.h>

#include <novo/gfx/rendering/cuboid.h>

#include <vector>
#include <random>

typedef detail::tvec4<u8, highp>		ubvec4;

RandomCubes::RandomCubes(u32 amount, i32 range, vec3 basePosition, vec3 scale):
	Entity(basePosition), Drawable("RandomCubes"),
	cbo(Buffer(BufferType::DrawCommand, "RandomCubes.cbo")),
	scale(scale)
{
	std::vector<vec4> positions(amount);
	std::vector<ubvec4> colors(amount);

	std::random_device rd;
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<i32> posDist(-range, range);
	std::uniform_int_distribution<u8> colDist(0, 255);

	for(uint i = 0; i < amount; i++) {
		positions[i] = vec4(posDist(rnd), posDist(rnd), posDist(rnd), 1);
		colors[i] = ubvec4(colDist(rnd), colDist(rnd), colDist(rnd), 255);
	}

	DrawElementsIndrectCommand cmd = {0,0,0,0,0};
	cmd.count = 36;
	cmd.instanceCount = amount;

	prog.attach(Shader::load(ShaderType::Vertex, "cubes.v.glsl", true, "RandomCubes.prog.vert"));
	prog.attach(Shader::load(ShaderType::Fragment, "cubes.f.glsl", true, "RandomCubes.prog.frag"));
	prog.use();

	prog.bindFragDataLocation(0, "color");

	vbo.allocateElements(BufferUsage::StaticDraw, Cuboid::vertices, positions, colors);

	vao.addAttribute(vbo, Cuboid::vertices, prog.getAttribute("basePos"), 4, DataType::Float);
	vao.addAttribute(vbo, positions, prog.getAttribute("cubePos"), positions[0].length(), DataType::Float);
	vao.addAttribute(vbo, colors, prog.getAttribute("cubeColor"), colors[0].length(), DataType::UByte, 0, true);

	ibo.setElements(BufferUsage::StaticDraw, Cuboid::indices);
	cbo.setData(BufferUsage::StaticDraw, cmd);


	glVertexAttribDivisor(prog.getAttribute("cubePos"), 1);
	glVertexAttribDivisor(prog.getAttribute("cubeColor"), 1);

	ibo.setElements(BufferUsage::StaticDraw, Cuboid::indices);
	cbo.setData(BufferUsage::StaticDraw, cmd);
	cbo.setLabel("RandomCubes.cbo");
}

void RandomCubes::draw(mat4 *transform)
{
	vao.bind();
	ibo.bind();
	cbo.bind();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	prog.setUniform("model", *transform * translate(glm::scale(mat4(), scale), pos));
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_BYTE, nullptr);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}
