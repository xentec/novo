#ifndef ORIGIN_H
#define ORIGIN_H

#include "entity.h"

#include <novo/gfx/drawable.h>

using novo::graphics::Drawable;

class Origin : public Entity, public Drawable
{
	f32 length, width;
public:
	Origin(f32 length = 1.0, f32 width = 2.0);
	void draw(mat4* transform);
};

#endif // ORIGIN_H
