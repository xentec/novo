#ifndef ENTITY_H
#define ENTITY_H

#include <novo/global.h>
#include <glm/glm.hpp>

namespace novo {
namespace entities {

using glm::vec3;

class Entity
{
protected:
	vec3 pos;
public:
	Entity(vec3 position);

	vec3 getPosition() const;
	void setPosition(const vec3& new_pos);
};

}}

#endif // ENTITY_H
