#pragma once

#include "novo/global.h"

#include <glm/glm.hpp>

namespace novo {
namespace gfx {

struct Camera
{
	static void spaceRotation(glm::quat& rot, f32 pitch, f32 yaw, f32 roll);
	static void fpsRotation(glm::quat& rot, f32 pitch, f32 yaw, f32 roll);

	static const struct WorldAxis { glm::vec3 x, y, z; } world;
};

}}
