#include "control.h"

#include "novo/component/controllable.h"
#include "novo/component/motion.h"
#include "novo/component/screen.h"

#include "novo/app.h"
#include "novo/gfx/camera.h"

#include "ext/glm_print.h"

#include <GLFW/glfw3.h>



using namespace novo::system;
using namespace novo::component;

using glm::vec3;
using glm::vec2;
using glm::quat;

//TODO: Input states/command tree
PlayerControl::PlayerControl():
	mod(0), keys(), cursor{ vec2(), vec2() }
{}

void PlayerControl::configure(EventManager& evm)
{
	f64 x, y;
	App::getMe().getWindow().getCursorPos(x, y);
	cursor.curr = cursor.prev = vec2{ x, y };
	DBG(4, "{}", cursor.prev);
}

void PlayerControl::update(EntityManager& es, EventManager& evm, f32 dt)
{
	vec3 dir, rot;
	f32 mul = 1.0f;

	dir = vec3(keys[GLFW_KEY_A] - keys[GLFW_KEY_D],
			   keys[GLFW_KEY_SPACE] - keys[GLFW_KEY_C],
			   keys[GLFW_KEY_W] - keys[GLFW_KEY_S]);

	mul *= 2 * (mod & GLFW_MOD_SHIFT) + !(mod & GLFW_MOD_SHIFT);

	// axis correction (x: yaw; y: pitch)
	rot = vec3{ cursor.curr.y - cursor.prev.y,  cursor.prev.x - cursor.curr.x, 0 };
	rot += vec3(keys[GLFW_KEY_DOWN] - keys[GLFW_KEY_UP],
				keys[GLFW_KEY_LEFT] - keys[GLFW_KEY_RIGHT],
				(keys[GLFW_KEY_PAGE_DOWN] | keys[GLFW_KEY_E]) - (keys[GLFW_KEY_DELETE] | keys[GLFW_KEY_Q]));

	cursor.prev = cursor.curr;


	bool reset = mod & GLFW_MOD_CONTROL && keys[GLFW_KEY_SPACE];

	ComponentHandle<Controllable> ctrl;
	ComponentHandle<Position> pos;
	ComponentHandle<Motion> mov;

	for(Entity e: es.entities_with_components(ctrl, pos, mov))
	{
		switch(ctrl->mode)
		{
		case Controllable::Mode::FPS:
			gfx::Camera::fpsRotation(pos->dir, rot.x, rot.y, rot.z);
			mov->v = pos->dir * dir * mul;
			if(!(dir.x && dir.z) && dir.y)
				mov->v = dir * mul;
			DBG(1, "{}", mov->v);
			break;
		case Controllable::Mode::SPACE:
			gfx::Camera::spaceRotation(pos->dir, rot.x, rot.y, rot.z);
			mov->v = pos->dir * dir * mul;
			break;
		}

		if(reset) {
			mov->a = vec3();
			mov->v = vec3();
			pos->dir = quat();
		}
	}
}

void PlayerControl::receive(const event::Key& ev)
{
	switch(ev.action) {
		case GLFW_PRESS:
			keys[ev.key] = true;
			break;
		case GLFW_RELEASE:
			keys[ev.key] = false;
			break;
	}
	mod = ev.mod;
}

void PlayerControl::receive(const event::Cursor& ev)
{
	cursor.curr = vec2{ ev.x, ev.y };
}

