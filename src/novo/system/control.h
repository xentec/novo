#pragma once

#include "novo/input.h"
#include "novo/system.h"

#include <glm/vec2.hpp>

#include <array>

namespace novo {

using entityx::Receiver;

namespace system {

struct PlayerControl: System<PlayerControl>, Receiver<PlayerControl>
{
	PlayerControl();

	virtual void configure(EventManager& evm);
	virtual void update(EntityManager& es, EventManager& evm, f32 dt);

	void receive(const event::Key& ev);
	void receive(const event::Cursor& ev);
private:
	u8 mod;
	std::array<bool, GLFW_KEY_LAST> keys;
	struct { glm::vec2 curr, prev; } cursor;

};

}}