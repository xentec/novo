#pragma once

#include "novo/component.h"
#include "novo/gfx/drawable.h"

#include <glm/glm.hpp>

namespace novo {
namespace component {

enum class DrawableType
{
	NORMAL,
	VIRTUAL
};

template<DrawableType TYPE = DrawableType::NORMAL>
struct BaseDrawable
{
	BaseDrawable(ptrS<gfx::Drawable> drawable, const glm::vec4 &color, glm::mat4 transform = glm::mat4()):
		color(color), matrix(transform), drawable(drawable) {}

	DrawableType type = TYPE;
	glm::vec4 color;
	glm::mat4 matrix;
	ptrS<gfx::Drawable> drawable;
};

using Drawable = BaseDrawable<>;
using Virtual = BaseDrawable<DrawableType::VIRTUAL>;

}}
