#include "randomcubes.h"

#include <novo/gfx/rendering/cuboid.h>
#include <novo/gfx/gl/obj.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <random>

using namespace novo::graphics;
using namespace gl;

RandomCubes::RandomCubes(u32 amount, i32 range, vec3 basePosition, vec3 scale):
	Entity(basePosition), Drawable(),
	cbo(Buffer(buffer::DrawCommand))
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

	vbo.reserve(vxSize + posSize + colSize, buffer::StaticDraw);
	vbo.setSubElements(0, Cuboid::vertices.size(), Cuboid::vertices.data());
	vbo.setSubElements(vxSize, positions.size(), positions.data());
	vbo.setSubElements(vxSize + posSize, colors.size(), colors.data());

	ibo.setData(Cuboid::indices.size(), Cuboid::indices.data(), buffer::StaticDraw);

	cbo.setData(cmd, buffer::StaticDraw);

	glBindVertexArray(vao);

	prog = util::createProgramFromFiles("cubes.v.glsl", "cubes.f.glsl");
	glUseProgram(prog);

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

	glUseProgram(0);

}

RandomCubes::~RandomCubes()
{
}

void RandomCubes::draw(mat4 *transform)
{
	glBindVertexArray(vao);
	ibo.bind();
	cbo.bind();
	glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(*transform * translate(scale(mat4(), vec3(2,2,2)), pos)));
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_BYTE, nullptr);
}
