#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <novo/global.h>
#include <novo/gfx/camera.h>
#include <novo/gfx/drawable.h>
#include <novo/gfx/renderer.h>

namespace novo {
namespace graphics {

class Framebuffer : public Drawable, public Renderer
{
	uint fb;
	uint cb, rbo;

	bool bound;

	sptr<Camera> cam;

/*
	-1,-1 ---------- 1,-1
	  |  \            |
	  |       \       |
	  |            \  |
	-1,1 ----------- 1,1
*/
public:
	Framebuffer(i32 width, i32 height, sptr<Camera> camera, bool bind = false);
	~Framebuffer();

	void bind();
	void unbind();
	void resize(i32 width, i32 height);

	virtual void draw(mat4* = nullptr);
	virtual void render(Drawable *obj);

	sptr<Camera> getCamera();
};

}
}

#endif // FRAMEBUFFER_H
