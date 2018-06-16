#pragma once

#include <glm/glm.hpp>

#include <fmt/format.h>

namespace fmt
{

template<class T, glm::length_t L, glm::qualifier Q>
struct formatter<glm::vec<L,T,Q>>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template <class FormatContext>
	auto format(const glm::vec<L,T,Q> &v, FormatContext &ctx)
	{
		auto b = ctx.begin();
		format_to(b, "{{");

		for(glm::length_t i = 0; i < L-1; i++)
			format_to(b, "{},", v[i]);

		return format_to(b, "{}}}", v[L-1]);
	}
};

template<class T, glm::length_t C, glm::length_t R, glm::qualifier Q>
std::ostream &operator<<(std::ostream &os, const glm::mat<C,R,T,Q> &m)
{
	return os << '{' << fmt::format(
					 "mat4x4\n"
					 "({:5.2f} {:5.2f} {:5.2f} {:5.2f})\n"
					 "({:5.2f} {:5.2f} {:5.2f} {:5.2f})\n"
					 "({:5.2f} {:5.2f} {:5.2f} {:5.2f})\n"
					 "({:5.2f} {:5.2f} {:5.2f} {:5.2f})",
					 m[0][0], m[0][1], m[0][2], m[0][3],
					 m[1][0], m[1][1], m[1][2], m[1][3],
					 m[2][0], m[2][1], m[2][2], m[2][3],
					 m[3][0], m[3][1], m[3][2], m[3][3]
				 ) << '}';
}

}
