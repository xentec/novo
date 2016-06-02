#pragma once

#include "novo/global.h"

#include <glm/glm.hpp>
#include <array>

namespace novo {
namespace gfx {
namespace primitive {

static const struct Plane
{
	Plane() {}
	std::array<glm::vec3, 4> vertices = {{
		{-0.5, -0.5, 0 },	//0
		{ 0.5, -0.5, 0 },	//1
		{-0.5,  0.5, 0 },	//2
		{ 0.5,  0.5, 0 },	//3
	}};
	std::array<glm::vec3, 4> vertices0 = {{
		{ 0, 0, 0 },	//0
		{ 1, 0, 0 },	//1
		{ 0, 1, 0 },	//2
		{ 1, 1, 0 },	//3
	}};

	std::array<glm::vec2, 4> texes = {{
		{0, 0},	//0
		{1, 0},	//1
		{0, 1},	//2
		{1, 1},	//3
	}};

	std::array<u32, 3*2> indices = {{
		0, 2, 3,
		3, 1, 0,
	}};

} plane;

}}}
