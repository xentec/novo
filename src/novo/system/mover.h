#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Mover final: System<Mover>
{
	virtual void update(EntityManager &es, EventManager &evm, TimeDelta dt) override;
private:
	TimeDelta time = 0;
};

}}
