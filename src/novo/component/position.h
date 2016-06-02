#pragma once

#include "novo/component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace novo {
namespace component {

struct Position
{
	Position(f32 x, f32 y, f32 z): Position(glm::vec3(x,y,z)) {}
	Position(const glm::vec3& pos = glm::vec3(), const glm::quat& dir = glm::quat()): curr(pos), prev(0), dir(dir) {}

	glm::vec3 curr, prev;
	glm::quat dir;
};

}}
