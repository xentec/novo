#include "randomcubes.h"

#include <novo/util.h>

#include <novo/gfx/rendering/cuboid.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <random>

typedef detail::tvec4<u8, highp>		ubvec4;

RandomCubes::RandomCubes(u32 amount, i32 range, vec3 basePosition, vec3 scale):
	Entity(basePosition), Drawable(),
	cbo(Buffer(BufferType::DrawCommand, BufferUsage::StaticDraw))
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

	prog.setLabel("RandomCubes");
	prog.attach(Shader::load(ShaderType::Vertex, "cubes.v.glsl"));
	prog.attach(Shader::load(ShaderType::Fragment, "cubes.f.glsl"));
	prog.use();

	prog.bindFragDataLocation(0, "color");

	vbo.allocateElements(Cuboid::vertices, positions, colors);

	vao.addAttribute(vbo, Cuboid::vertices, prog.getAttribute("basePos"), 4, DataType::Float);
	vao.addAttribute(vbo, positions, prog.getAttribute("cubePos"), positions[0].length(), DataType::Float);
	vao.addAttribute(vbo, colors, prog.getAttribute("cubeColor"), colors[0].length(), DataType::UByte, 0, true);

	ibo.setElements(Cuboid::indices);
	cbo.setData(cmd);


	glVertexAttribDivisor(prog.getAttribute("cubePos"), 1);
	glVertexAttribDivisor(prog.getAttribute("cubeColor"), 1);
}

void RandomCubes::draw(mat4 *transform)
{
	vao.bind();
	ibo.bind();
	cbo.bind();
	glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(*transform * translate(scale(mat4(), vec3(2,2,2)), pos)));
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_BYTE, nullptr);
}
