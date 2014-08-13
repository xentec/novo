#ifndef CUBOID_H
#define CUBOID_H

#include <novo/global.h>

#include <array>

class Cuboid
{
public:
/*
	static const f32 vertices[4*4*2];
	static const u8 indices[(3*2)*6];
*/
	static const std::array<f32, 4*4*2> vertices;
	static const std::array<u8, (3*2)*6> indices;
};


#endif // CUBOID_H
