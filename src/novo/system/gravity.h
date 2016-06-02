#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Gravity: System<Gravity>
{
	void update(EntityManager &entities, EventManager &evm, f32 dt) override;

};

}}
