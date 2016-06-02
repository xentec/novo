#pragma once

#include "novo/system.h"
#include "novo/gfx/shader.h"

namespace novo {
namespace system {

struct Renderer : System<Renderer>
{
	Renderer();

	void addShader(const gfx::Shader& shader);

	virtual void configure(EventManager& evm);
	virtual void update(EntityManager &es, EventManager &evm, f32 dt);
private:
	std::vector<gfx::Shader> shaders;
};

}}
