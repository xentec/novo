#include "randomcubes.h"

#include <novo/gfx/rendering/cuboid.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <random>

typedef detail::tvec4<u8, highp>		ubvec4;

using namespace novo::graphics;
using namespace gl;

RandomCubes::RandomCubes(u32 amount, i32 range, vec3 basePosition, vec3 scale):
	Entity(basePosition), Drawable(),
	cbo(Buffer(buffer::DrawCommand, buffer::StaticDraw))
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

	size_t vxSize = Cuboid::vertices.size() * sizeof(Cuboid::vertices[0]);
	size_t posSize = positions.size() * sizeof(positions[0]);
	size_t colSize = colors.size() * sizeof(colors[0]);

	vbo.allocate(vxSize + posSize + colSize);
	vbo.addSubElements(Cuboid::vertices);
	vbo.addSubElements(positions);
	vbo.addSubElements(colors);

	ibo.setElements(Cuboid::indices);

	cbo.setData(cmd);

	vao.bind();

	prog.setLabel("RandomCubes");
	prog.attach(Shader::load(shader::Vertex, "cubes.v.glsl"));
	prog.attach(Shader::load(shader::Fragment, "cubes.f.glsl"));
	prog.setFragDataLocation(0, "color");
	prog.use();

	GLint atribBasePos = glGetAttribLocation(prog, "basePos");
	glVertexAttribPointer(atribBasePos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(atribBasePos);

	GLint atribCubePos = glGetAttribLocation(prog, "cubePos");
	glVertexAttribPointer(atribCubePos, 4, GL_FLOAT, GL_FALSE, 0, (void*) vxSize);
	glEnableVertexAttribArray(atribCubePos);
	glVertexAttribDivisor(atribCubePos, 1);

	GLint atribCubeColor = glGetAttribLocation(prog, "cubeColor");
	glVertexAttribPointer(atribCubeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) (vxSize + posSize));
	glEnableVertexAttribArray(atribCubeColor);
	glVertexAttribDivisor(atribCubeColor, 1);
}

RandomCubes::~RandomCubes()
{
}

void RandomCubes::draw(mat4 *transform)
{
	vao.bind();
	ibo.bind();
	cbo.bind();
	glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(*transform * translate(scale(mat4(), vec3(2,2,2)), pos)));
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_BYTE, nullptr);
}
