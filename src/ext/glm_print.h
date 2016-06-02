#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cppformat/format.h>

#include <ostream>

namespace glm {

template <typename T, precision P>
std::ostream &operator<<(std::ostream &os, const tvec1<T,P> &v)
{
	return os << '{' << v.x << '}';
}

template <typename T, precision P>
std::ostream &operator<<(std::ostream &os, const tvec2<T,P> &v)
{
	return os << '{' << v.x << ';' << v.y << '}';
}

template <typename T, precision P>
std::ostream &operator<<(std::ostream &os, const tvec3<T,P> &v)
{
	return os << '{' << v.x << ';' << v.y << ';' << v.z << '}';
}

template <typename T, precision P>
std::ostream &operator<<(std::ostream &os, const tvec4<T,P> &v)
{
	return os << '{' << v.x << ';' << v.y << ';' << v.z << ';' << v.w << '}';
}

template <typename T, precision P>
std::ostream &operator<<(std::ostream &os, const tmat4x4<T,P> &m)
{
	return os << '{' << fmt::sprintf(
					 "mat4x4\n"
					 "(%5.2f %5.2f %5.2f %5.2f)\n"
					 "(%5.2f %5.2f %5.2f %5.2f)\n"
					 "(%5.2f %5.2f %5.2f %5.2f)\n"
					 "(%5.2f %5.2f %5.2f %5.2f)",
					 m[0][0], m[0][1], m[0][2], m[0][3],
					 m[1][0], m[1][1], m[1][2], m[1][3],
					 m[2][0], m[2][1], m[2][2], m[2][3],
					 m[3][0], m[3][1], m[3][2], m[3][3]
				 ) << '}';
}

}
