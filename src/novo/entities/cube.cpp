#include "cube.h"

#include <novo/gfx/rendering/cuboid.h>
#include <novo/gfx/gl/obj.h>

using namespace novo::graphics;

Cube::Cube(vec3 position, float size):
	Entity(position), Drawable()
{

	util::createBuffers({&cbo});
/*	DrawElementsIndrectCommand cmd = {0,0,0,0,0};
	cmd.count = 36;
	cmd.instanceCount = amount;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cuboid::vertices) + posSize + colSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Cuboid::vertices), &Cuboid::vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Cuboid::vertices), posSize, &*positions.begin());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Cuboid::vertices) + posSize, colSize, &*colors.begin());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cuboid::indices), &Cuboid::indices, GL_STATIC_DRAW);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cbo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd), &cmd, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	prog = util::createProgramFromFiles("cubes.v.glsl", "cubes.f.glsl");
	glUseProgram(prog);

	GLint atribPos = glGetAttribLocation(prog, "pos");
	glVertexAttribPointer(atribBasePos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(atribBasePos);

	GLint atribCubeColor = glGetAttribLocation(prog, "color");
	glVertexAttribPointer(atribCubeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) (sizeof(Cuboid::vertices) + posSize));
	glEnableVertexAttribArray(atribCubeColor);
	glVertexAttribDivisor(atribCubeColor, 1);

	glUseProgram(0);
*/
}

Cube::~Cube()
{
	util::destroyBuffers({cbo});
}


void Cube::draw(mat4* tranform)
{

}
