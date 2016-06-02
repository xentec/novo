#pragma once

#include "novo/global.h"
#include "novo/gfx/gl/gl.h"
#include "novo/gfx/drawable.h"
#include "novo/gfx/renderer.h"

namespace novo {
namespace gfx {

struct Screen : Drawable, Renderer
{
	Screen(i32 width, i32 height, f32 fov = 90, f32 near = 1, f32 far = -1, gl::Framebuffer fb = gl::Framebuffer());
	virtual ~Screen();

	void resize(i32 width, i32 height);
	void clear(glm::vec4 color = glm::vec4(0.2, 0.2, 0.2, 1.0));

	void update(Shader& shader) const;
	void use();

	virtual void draw(Shader* shader = nullptr);
	virtual void render(Drawable *obj, Shader* mvp);

	void setProjection(f32 fov, f32 near, f32 far);
	void setView(const glm::vec3& pos, const glm::quat& rot);

private:
	gl::Buffer vbo;
	gl::VertexArray vao;

	gl::Framebuffer fb;
	gl::Texture cbo;
	gl::Renderbuffer rbo;

	Shader shader;

	f32 aspect;
	glm::mat4 proj, view;
};

}
}
