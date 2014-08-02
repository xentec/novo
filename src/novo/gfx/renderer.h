#ifndef RENDERER_H
#define RENDERER_H

#include <novo/gfx/drawable.h>

namespace novo {
namespace graphics {

class Renderer
{
public:
	virtual void render(Drawable*) = 0;
};

}}

#endif // RENDERER_H
