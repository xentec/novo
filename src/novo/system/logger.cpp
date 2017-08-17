#include "logger.h"

#include "novo/component/controllable.h"
#include "novo/component/motion.h"
#include "novo/component/position.h"

#include <glm/gtx/string_cast.hpp>

using namespace novo::component;
using namespace novo::system;

using glm::to_string;

void Logger::update(EntityManager& es, EventManager& evm, f32 dt)
{
	ComponentHandle<Controllable> player;
	ComponentHandle<Motion> mov;
	ComponentHandle<Position> pos;

	for(const Entity& e: es.entities_with_components(pos, mov, player)) {
		DBG(5, "{}: {}, {}, {}", e.id().id(), to_string(mov->a), to_string(mov->v), to_string(pos->curr));
	}
}


