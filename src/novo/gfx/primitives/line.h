#pragma once

#include "novo/global.h"

#include <glm/glm.hpp>
#include <array>

namespace novo {
namespace gfx {
namespace primitive {

static const struct Line
{
	Line() {}
	std::array<glm::vec3, 2> vertices = {{
		{ 0, 0, 0 },	//0
		{ 1, 1, 1 },	//1
	}};

	std::array<u32, 2> indices = {
		0, 1,
	};

} line;

}}}
