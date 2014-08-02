#ifndef CUBE_H
#define CUBE_H

#include <novo/entities/entity.h>
#include <novo/gfx/drawable.h>

using namespace glm;

using novo::entities::Entity;
using novo::graphics::Drawable;

class Cube : public Entity, public Drawable
{
	GLuint cbo;
public:
	Cube(vec3 position, float size);
	~Cube();
	void draw(mat4 *tranform);
};

#endif // CUBE_H
