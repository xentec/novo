#ifndef CAMERA_H
#define CAMERA_H

#include <novo/entities/entity.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;
using novo::entities::Entity;

class Camera : public Entity
{
	vec3 pos;
	quat rot;

	vec3 velocity;

	vec3 forward, up, right;

	struct {
		float width, height;
		float fov;
		float near, far;
	} persp;

	vec2 mousePos;
public:
	Camera(vec3 position, float width, float height, float fov = 90, float near = 1, float far = -1);

	mat4 getView() const;
	mat4 getProjection() const;

	float getFOV() const;
	void setFOV(float new_fov);

	float getNearPlane() const;
	void setNearPlane(float new_near);
	float getFarPlane() const;
	void setFarPlane(float new_far);

	void resize(float new_width, float new_height);

	void moveRelative(vec3 rel_pos);
	void moveDirected(vec3 rel_pos);
	void moveUpdate(float dt);
	vec3 getVelocity() const;
	void setVelocity(vec3 vel);

	void pitch(float a);
	void yaw(float a);
	void roll(float a);

	void mouseCallback(double x, double y);
};

#endif // CAMERA_H
