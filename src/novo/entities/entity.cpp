#include "entity.h"

using namespace novo::entities;

Entity::Entity(vec3 position):
	pos(position)
{}

vec3 Entity::getPosition() const
{
	return pos;
}

void Entity::setPosition(const glm::vec3& new_pos)
{
	pos = new_pos;
}
