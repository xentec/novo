#pragma once

#include "novo/system.h"

namespace novo {
namespace system {

struct Logger final : System<Logger>
{
	virtual void update(EntityManager &es, EventManager &evm, TimeDelta dt) override;
};

}}
