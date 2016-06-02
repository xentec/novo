#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Logger : System<Logger>
{
	void update(EntityManager &es, EventManager &evm, f32 dt);
};

}}
