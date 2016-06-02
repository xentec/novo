#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Mover: System<Mover>
{
	virtual void update(EntityManager &es, EventManager &evm, f32 dt);
private:
	f64 time = 0;
};

}}
