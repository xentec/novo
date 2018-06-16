#include "logger.h"

#include "novo/component/controllable.h"
#include "novo/component/motion.h"
#include "novo/component/position.h"

#include "ext/glm_print.h"

using namespace novo::component;
using namespace novo::system;

void Logger::update(EntityManager& es, EventManager&, TimeDelta)
{
	fmt::memory_buffer buf;
	es.each<Position, Motion>([&](Entity e, const Position& pos, const Motion& mov)
	{
		if(pos.prev == pos.curr) return;

		fmt::format_to(buf, "{}: {}, {}, {}\n", e.id().index(), mov.a, mov.v, pos.curr);
	});

	fmt::print("{}", fmt::to_string(buf));
}


