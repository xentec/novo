#ifndef RANDOMCUBES_H
#define RANDOMCUBES_H

#include "entity.h"
#include <novo/gfx/drawable.h>

using namespace glm;

using novo::entities::Entity;
using novo::graphics::Drawable;

class RandomCubes : public Entity, public Drawable
{
	Buffer cbo;
	vec3 scale;
public:
	RandomCubes(uint amount, i32 range, vec3 basePosition, vec3 scale = vec3(10));

	void draw(mat4 *transform);
};

#endif // RANDOMCUBES_H
