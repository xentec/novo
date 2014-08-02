#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>


#include <iostream>

Camera::Camera(vec3 position, float width, float height, float fov, float near, float far):
	Entity(position),
	rot(quat()),
	velocity(0),
	persp{width,height,fov,near,far}
{
	right = glm::normalize(glm::cross(forward, up));
}

///TODO: Caching
mat4 Camera::getView() const
{
	return glm::mat4_cast(glm::inverse(rot)) * glm::translate(mat4(), pos);
}

mat4 Camera::getProjection() const
{
	return glm::perspective(glm::radians(persp.fov), persp.width / persp.height, persp.near, persp.far);
}


float Camera::getFOV() const
{
	return persp.fov;
}

void Camera::setFOV(float new_fov)
{
	persp.fov = new_fov;
}

float Camera::getNearPlane() const
{
	return persp.near;
}

void Camera::setNearPlane(float new_near)
{
	persp.near = new_near;
}

float Camera::getFarPlane() const
{
	return persp.far;
}

void Camera::setFarPlane(float new_far)
{
	persp.far = new_far;
}

void Camera::resize(float new_width, float new_height)
{
/*	if(persp.width == new_width &&
	   persp.height == new_height)
		return;
*/
	persp.width = new_width;
	persp.height = new_height;
}


void Camera::moveRelative(vec3 rel_pos)
{
	pos += rel_pos;
}

void Camera::moveDirected(vec3 rel_pos)
{
	pos += rot * rel_pos;
}

void Camera::moveUpdate(float dt)
{
	moveDirected(velocity*dt);
}

vec3 Camera::getVelocity() const
{
	return velocity;
}

void Camera::setVelocity(vec3 vel)
{
	velocity = vel;
}

void Camera::pitch(float a)
{
	rot = rot * glm::angleAxis(glm::radians(a), forward);
}

void Camera::yaw(float a)
{
	rot = glm::angleAxis(glm::radians(a), up) * rot;
}

void Camera::roll(float a)
{
	rot = rot * glm::angleAxis(glm::radians(a), right);
}

void Camera::mouseCallback(double x, double y)
{
	yaw(mousePos.x - x);
	pitch(mousePos.y - y);

	mousePos = vec2(x,y);
}

