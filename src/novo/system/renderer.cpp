#include "renderer.h"

#include "novo/component/controllable.h"
#include "novo/component/drawable.h"
#include "novo/component/position.h"
#include "novo/component/screen.h"

#include "novo/gfx/shader.h"

#include "novo/gfx/primitives/cuboid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace novo::system;
using namespace novo::component;
using namespace novo::gl::glb;

using novo::gfx::primitive::cuboid;

Renderer::Renderer():
	System<Renderer>(),
	shaders()
{}

void Renderer::addShader(const gfx::Shader& shader)
{
	shaders.push_back(shader);
}

void Renderer::configure(EventManager&)
{
	for(gfx::Shader& shader : shaders)
		shader.compile();
}

void Renderer::update(EntityManager& es, EventManager&, TimeDelta)
{
	gl::enable(GL_DEPTH_TEST);
	gl::enable(GL_CULL_FACE);

	es.each<Screen, Position>([&](Entity, const Screen& scr_comp, const Position& plyPos)
	{
		auto &scr = *scr_comp.screen;
		scr.setView(plyPos.curr, plyPos.dir);
		scr.use();

		{
			gfx::Shader& shader = shaders[0];

			scr.update(shader);
			shader.use();

			es.each<Virtual, Position>([&](Entity, const Virtual& drw, const Position& entPos)
			{
				shader["color"] = drw.color;
				shader["model"] = glm::translate(glm::mat4_cast(entPos.dir), entPos.curr) * drw.matrix;
				drw.drawable->draw(&shader);
			});
		}
		{
			for(gfx::Shader& shader: shaders)
			{
				scr.update(shader);
				shader.use();

				es.each<Drawable, Position>([&](Entity, const Drawable& drw, const Position& entPos)
				{
					shader["color"] = drw.color;
					shader["model"] = glm::translate(glm::mat4_cast(entPos.dir), entPos.curr) * drw.matrix;
					drw.drawable->draw(&shader);
				});
			}
		}
	});

	gl::disable(GL_CULL_FACE);
	gl::disable(GL_DEPTH_TEST);
}
