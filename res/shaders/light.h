#pragma once

#include "novo/component.h"
#include "novo/gfx/mesh.h"

#include <glm/glm.hpp>

namespace novo {
namespace component {

struct Light
{
	enum class Type
	{

	};

	Light(const glm::vec4 &color):
		color(color)
	{}

	glm::vec4 color;
};


}}

