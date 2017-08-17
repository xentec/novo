#include "world.h"

#include "novo/gfx/mesh.h"
#include "novo/gfx/primitives/cuboid.h"

#include "novo/component/position.h"
#include "novo/component/mass.h"
#include "novo/component/motion.h"
#include "novo/component/drawable.h"
#include "novo/component/controllable.h"

#include "novo/system.h"
#include "novo/system/gravity.h"
#include "novo/system/control.h"
#include "novo/system/mover.h"
#include "novo/system/renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <fmt/format.h>
#include <random>

using namespace entityx;

using namespace novo;
using namespace component;
using namespace system;

World::World(i32 size)
{
	std::random_device rd;
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<i32> PD(-size, size);
	std::uniform_real_distribution<f32> MD(1.0, 1000000000.0);
	std::uniform_real_distribution<f32> CD(0.0, 1.0);

	Entity e;
	auto mdl = std::make_shared<gfx::Mesh>(gfx::Mesh::fromPrimitive(gfx::primitive::cuboid));

//*/
	for(i32 i = 0; i < size; i++)
	{
		e = entities.create();
		e.assign<Position>(PD(rnd), PD(rnd), PD(rnd));
		e.assign<Drawable>(mdl, glm::vec4(CD(rnd),CD(rnd),CD(rnd),1.0f));

		e.assign<Motion>();
		e.assign<Mass>(1000000000.0f);
	}
/*
	e = entities.create();
	e.assign<Position>(1, 0, 0);
	e.assign<Virtual>(mdl, glm::vec4(1, 0, 0, 1), glm::scale(glm::mat4(), glm::vec3(size, 1, 1)));
	e = entities.create();
	e.assign<Position>(0, 1, 0);
	e.assign<Virtual>(mdl, glm::vec4(0, 1, 0, 1), glm::scale(glm::mat4(), glm::vec3(1, size, 1)));
	e = entities.create();
	e.assign<Position>(0, 0, 1);
	e.assign<Virtual>(mdl, glm::vec4(0, 0, 1, 1), glm::scale(glm::mat4(), glm::vec3(1, 1, size)));
	e = entities.create();
	e.assign<Position>(0, 0, 0);
	e.assign<Virtual>(mdl, glm::vec4(0), glm::scale(glm::mat4(), glm::vec3(.2, .2, .2)));


	e = entities.create();
	e.assign<Position>(5,5,5);
	e.assign<Drawable>(mdl, glm::vec4(1), glm::scale(glm::mat4(), glm::vec3(2, 2, 2)));
*/
/*/
	e = entities.create();
	e.assign<Position>(1, 0, 0);
	e.assign<Drawable>(mdl, glm::vec4(1, 0, 1, 1), glm::scale(glm::mat4(), glm::vec3(size/2, .5, .5)));
	e.assign<Controllable>();
	e = entities.create();
	e.assign<Position>(0, 1, 0);
	e.assign<Drawable>(mdl, glm::vec4(1, 1, 0, 1), glm::scale(glm::mat4(), glm::vec3(.5, size/2, .5)));
	e.assign<Controllable>();
	e = entities.create();
	e.assign<Position>(0, 0, 1);
	e.assign<Drawable>(mdl, glm::vec4(0, 1, 1, 1), glm::scale(glm::mat4(), glm::vec3(.5, .5, size/2)));
	e.assign<Controllable>();

	e = entities.create();
	e.assign<Position>(glm::vec3(0));
	e.assign<Drawable>(mdl, glm::vec4(1), glm::scale(glm::mat4(), glm::vec3(.2, .2, 10)));
	e.assign<Controllable>();
	e = entities.create();
	e.assign<Position>(glm::vec3(-5,0,7));
	e.assign<Drawable>(mdl, glm::vec4(1), glm::scale(glm::mat4(), glm::vec3(10, .2, 1)));
	e.assign<Controllable>();
	e = entities.create();
	e.assign<Position>(glm::vec3(-2,0,3));
	e.assign<Drawable>(mdl, glm::vec4(1), glm::scale(glm::mat4(), glm::vec3(4, .2, 1)));
	e.assign<Controllable>();

//*/



	mdl->commit();

	systems.add<Gravity>();
	systems.add<Mover>();
	systems.configure();
}

void World::update(f32 dt)
{
//	fmt::print_colored(fmt::RED, "Update... "); fmt::print("({}) ", dt);

	ComponentHandle<Motion> mov;
	for(Entity e: entities.entities_with_components(mov)) {
		mov->a = glm::vec3(0);
	}
	systems.update<Gravity>(dt);
	systems.update<PlayerControl>(dt);
	systems.update<Mover>(dt);
//	systems.update<Logger>(dt);
}

void World::render(f32 dt)
{
//	fmt::print_colored(fmt::GREEN, "Render...");fmt::print("({}) ", dt);
	systems.update<Renderer>(dt);
}

