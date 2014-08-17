#include "cuboid.h"

//const f32 Cuboid::vertices[4*4*2]
const std::array<f32, 4*4*2> Cuboid::vertices
= {
	-0.5, -0.5, -0.5, 1,	//0
	 0.5, -0.5, -0.5, 1,	//1
	-0.5,  0.5, -0.5, 1,	//2
	 0.5,  0.5, -0.5, 1,	//3

	-0.5, -0.5,  0.5, 1,	//4
	 0.5, -0.5,  0.5, 1,	//5
	-0.5,  0.5,  0.5, 1,	//6
	 0.5,  0.5,  0.5, 1,	//7
};

//const u8 Cuboid::indices[(3*2)*6]
const std::array<u8, (3*2)*6> Cuboid::indices
= {
	0, 2, 3,  3, 1, 0, //Ground
	4, 5, 7,  7, 6, 4, //Top

	4, 0, 1,  1, 5, 4, //Left
	5, 1, 3,  3, 7, 5, //Front
	6, 2, 0,  0, 4, 6, //Back
	7, 3, 2,  2, 6, 7, //Right
};

