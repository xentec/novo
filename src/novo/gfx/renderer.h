#pragma once

namespace novo {
namespace gfx {

struct Drawable;
struct Shader;

struct Renderer
{
	virtual void render(Drawable*, Shader*) = 0;
};

}}
