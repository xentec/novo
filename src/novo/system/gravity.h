#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Gravity final: System<Gravity>
{
	virtual void update(EntityManager &entities, EventManager &evm, TimeDelta dt) override;
};

}}
