#pragma once

#include "position.h"

#include <functional>

namespace novo {
namespace component {

struct Motion
{
	Motion(glm::vec3 v = glm::vec3(), glm::vec3 a = glm::vec3()):
		v(v), a(a), accelerator([&](const Position&, f32){ return this->a; }) {}

	glm::vec3 v, a;
	glm::quat rotation;
	std::function<glm::vec3(const Position&, f32)> accelerator;
};

}}
