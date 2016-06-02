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

void Renderer::configure(EventManager& evm)
{
	for(gfx::Shader& shader : shaders)
		shader.compile();
}

void Renderer::update(EntityManager& es, EventManager& evm, f32 dt)
{
	gl::enable(GL_DEPTH_TEST);
	gl::enable(GL_CULL_FACE);

	ComponentHandle<Position> plyPos, entPos;
	ComponentHandle<Screen> scr;

	for(Entity e: es.entities_with_components(scr, plyPos))
	{
		scr->screen->setView(plyPos->curr, plyPos->dir);
		scr->screen->use();

		{
			ComponentHandle<Virtual> drw;
			gfx::Shader& shader = shaders[0];

			scr->screen->update(shader);
			shader.use();

			for(Entity e: es.entities_with_components(drw, entPos))
			{
				shader["color"] = drw->color;
				shader["model"] = glm::translate(glm::mat4_cast(entPos->dir), entPos->curr) * drw->matrix;
				drw->drawable->draw(&shader);
			}
		}
		{
			ComponentHandle<Drawable> drw;
			for(gfx::Shader& shader: shaders)
			{
				scr->screen->update(shader);
				shader.use();

				for(Entity e: es.entities_with_components(drw, entPos))
				{
					shader["color"] = drw->color;
					shader["model"] = glm::translate(glm::mat4_cast(entPos->dir), entPos->curr) * drw->matrix;
					drw->drawable->draw(&shader);
				}
			}
		}

	}

	gl::disable(GL_CULL_FACE);
	gl::disable(GL_DEPTH_TEST);
}
