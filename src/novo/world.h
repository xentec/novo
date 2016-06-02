#pragma once

#include "novo/global.h"

#include <entityx/entityx.h>

#include <map>
#include <unordered_map>
#include <vector>

namespace novo {

struct World : entityx::EntityX
{
	World(i32 size);
	void update(f32 dt);
	void render(f32 dt);
};

}