#include "mover.h"

#include "novo/component/motion.h"
#include "novo/component/position.h"

using namespace novo::system;
using namespace novo::component;

static void integrate(Position &pos, Motion &mov, f64 time, f32 dt);

void Mover::update(EntityManager& es, EventManager& evm, f32 dt)
{
	es.each<Position, Motion>([&](Entity e, Position& pos, Motion& mov)
	{
		pos.prev = pos.curr;
		integrate(pos, mov, time, dt);
	});

	time += dt;
}

// Thanks to http://gafferongames.com/game-physics/integration-basics/
// #####################################################################
using glm::vec3;

struct Derivative
{
	vec3 dx, dv;
};

inline
void evaluate(Derivative& out, const Position& init, const Motion& mov, const Derivative& dvt, f64 time, f32 dt)
{
	Position adv { init.curr + dvt.dx*dt };
	out.dx = mov.v + dvt.dv*dt;
	out.dv = mov.accelerator(adv, time+dt);
}

static
void integrate(Position& pos, Motion& mov, f64 time, f32 dt)
{
	Derivative a, b, c, d, _ = {vec3(), vec3()};
	evaluate(a, pos, mov, _, time, 0.0f),
	evaluate(b, pos, mov, a, time, dt*0.5f),
	evaluate(c, pos, mov, b, time, dt*0.5f),
	evaluate(d, pos, mov, c, time, dt);

	pos.curr += dt / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);
	mov.v    += dt / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);
}
