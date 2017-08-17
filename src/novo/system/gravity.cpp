#include "gravity.h"

#include "novo/component/mass.h"
#include "novo/component/motion.h"

using namespace novo::system;
using namespace novo::component;

using glm::vec3;

static const f32 G = 6.67384e-11;
//static const f32 G = 1.0f;
static std::vector<Entity> ents;

void Gravity::update(EntityManager& es, EventManager& evm, f32 dt)
{
	{
		EntityManager::View<Position, Motion, Mass> v = es.entities_with_components<Position, Motion, Mass>();
		ents.assign(v.begin(),v.end());
	}

	for (usz i = 0; i < ents.size(); i++) {
		Entity main = ents[i];
		vec3 mainPos = main.component<Position>()->curr;
		f32 g = -G * main.component<Mass>()->m;

		for (usz j = 0; j < i; j++) {
			Entity peer = ents[j];
			vec3 peerPos = peer.component<Position>()->curr;
			//ComponentHandle<Motion> v2 = peer.component<Motion>();

			vec3 distance = mainPos - peerPos;

			f32 dot = glm::dot(distance, distance);
			f32 r2 = glm::abs(dot);
			vec3 dir = distance * glm::inversesqrt(dot);

			peer.component<Motion>()->a += -g/r2 * dir;
		}
	}
/*	es.each<Position, Motion>([](Entity, Position& pos, Motion& mov)
	{
		mov.a += glm::normalize(pos.curr)/10.0f;
	});
*/
}
