#include "randomcubes.h"

#include <novo/gfx/rendering/cuboid.h>
#include <novo/gfx/gl/obj.h>

#include <vector>
#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace novo::graphics;

RandomCubes::RandomCubes(u32 amount, i32 range, vec3 basePosition, vec3 scale):
	Entity(basePosition), Drawable()
{
	std::vector<vec4> positions(amount);
	size_t posSize = positions.size() * sizeof(positions[0]);

	std::vector<ubvec4> colors(amount);
	size_t colSize = colors.size() * sizeof(colors[0]);


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

	util::createBuffers({&cbo});

	size_t vxSize = sizeof(Cuboid::vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vxSize + posSize + colSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vxSize, &Cuboid::vertices);
	glBufferSubData(GL_ARRAY_BUFFER, vxSize, posSize, &*positions.begin());
	glBufferSubData(GL_ARRAY_BUFFER, vxSize + posSize, colSize, &*colors.begin());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cuboid::indices), &Cuboid::indices, GL_STATIC_DRAW);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cbo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd), &cmd, GL_STATIC_DRAW);

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
	util::destroyBuffers({cbo});
}

void RandomCubes::draw(mat4 *transform)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cbo);
	glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(*transform * translate(scale(mat4(), vec3(2,2,2)), pos)));
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_BYTE, nullptr);
}
