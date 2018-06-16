#include "camera.h"

#include <glm/gtc/quaternion.hpp>

using namespace novo::gfx;
using namespace glm;

const Camera::WorldAxis Camera::world { {1,0,0}, {0,1,0}, {0,0,1} };

void Camera::spaceRotation(quat& rot, f32 pitch, f32 yaw, f32 roll)
{
	rot *= angleAxis(radians(pitch), world.x);
	rot *= angleAxis(radians(yaw),   world.y);
	rot *= angleAxis(radians(roll),  world.z);
}

void Camera::fpsRotation(quat& rot, f32 pitch, f32 yaw, f32 roll)
{
//	f64 p = glm::pitch(rot) + radians(pitch);
//	f64 y = glm::yaw(rot) + radians(yaw);
//	DBG(1, "P:{:.2f} Y:{:.2f}", glm::degrees(p), glm::degrees(y));
//	if(glm::abs(p) <= glm::half_pi<f64>())
	rot *= angleAxis(radians(pitch), world.x);
	rot =  angleAxis(radians(yaw),   world.y) * rot;
	rot *= angleAxis(radians(roll),  world.z);
}
