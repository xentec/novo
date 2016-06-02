#pragma once

#include "novo/global.h"

#include <glm/glm.hpp>
#include <array>

namespace novo {
namespace gfx {
namespace primitive {

static const struct Cuboid
{
	Cuboid(){}
	std::array<glm::vec3, 4*2> vertices = {{
		{-0.5f, -0.5f, -0.5f },	//0
		{ 0.5f, -0.5f, -0.5f },	//1
		{-0.5f,  0.5f, -0.5f },	//2
		{ 0.5f,  0.5f, -0.5f },	//3

		{-0.5f, -0.5f,  0.5f },	//4
		{ 0.5f, -0.5f,  0.5f },	//5
		{-0.5f,  0.5f,  0.5f },	//6
		{ 0.5f,  0.5f,  0.5f },	//7
	}};

	std::array<glm::vec3, 4*2> vertices0 = {{
		{ 0, 0, 0 },	//0
		{ 1, 0, 0 },	//1
		{ 0, 1, 0 },	//2
		{ 1, 1, 0 },	//3

		{ 0, 0, 1 },	//4
		{ 1, 0, 1 },	//5
		{ 0, 1, 1 },	//6
		{ 1, 1, 1 },	//7
	}};

	std::array<u32, (3*2)*6> indices = {{
		0, 2, 3,  3, 1, 0, //Ground
		4, 5, 7,  7, 6, 4, //Top

		4, 0, 1,  1, 5, 4, //Left
		5, 1, 3,  3, 7, 5, //Front
		6, 2, 0,  0, 4, 6, //Back
		7, 3, 2,  2, 6, 7, //Right
	}};

	std::array<glm::vec2, 4*2> texes;
} cuboid;

}}}
