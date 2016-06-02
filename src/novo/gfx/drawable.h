#pragma once

#include "novo/gfx/shader.h"

#include <glm/glm.hpp>

namespace novo {
namespace gfx {

struct Drawable
{
	virtual void draw(Shader* shader) = 0;
};

}}
