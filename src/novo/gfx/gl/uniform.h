#pragma once

#include "object.h"

#include <glm/glm.hpp>

namespace novo {
namespace gl {

struct Program;

struct Uniform
{
	Uniform();
	Uniform(const Uniform &other);

	template<class T>
	inline void set(const T& value) { set(1, value); }

	template<class T>
	inline void set(i32 count, const T& value, bool transpose = false) { set(count, value, transpose); }

	// Helper
	void set(i32 count, const f32& value);
	void set(i32 count, const f64& value);
	void set(i32 count, const i32& value);
	void set(i32 count, const u32& value);

	void set(i32 count, const glm::vec2& value);
	void set(i32 count, const glm::dvec2& value);
	void set(i32 count, const glm::ivec2& value);
	void set(i32 count, const glm::uvec2& value);

	void set(i32 count, const glm::vec3& value);
	void set(i32 count, const glm::dvec3& value);
	void set(i32 count, const glm::ivec3& value);
	void set(i32 count, const glm::uvec3& value);

	void set(i32 count, const glm::vec4& value);
	void set(i32 count, const glm::dvec4& value);
	void set(i32 count, const glm::ivec4& value);
	void set(i32 count, const glm::uvec4& value);


	void set(i32 count, const glm::mat2& value, bool transpose = false);
	void set(i32 count, const glm::dmat2& value, bool transpose = false);

	void set(i32 count, const glm::mat3& value, bool transpose = false);
	void set(i32 count, const glm::dmat3& value, bool transpose = false);

	void set(i32 count, const glm::mat4& value, bool transpose = false);
	void set(i32 count, const glm::dmat4& value, bool transpose = false);


	void set(i32 count, const glm::mat2x3& value, bool transpose = false);
	void set(i32 count, const glm::dmat2x3& value, bool transpose = false);

	void set(i32 count, const glm::mat3x2& value, bool transpose = false);
	void set(i32 count, const glm::dmat3x2& value, bool transpose = false);

	void set(i32 count, const glm::mat2x4& value, bool transpose = false);
	void set(i32 count, const glm::dmat2x4& value, bool transpose = false);

	void set(i32 count, const glm::mat4x2& value, bool transpose = false);
	void set(i32 count, const glm::dmat4x2& value, bool transpose = false);

	void set(i32 count, const glm::mat3x4& value, bool transpose = false);
	void set(i32 count, const glm::dmat3x4& value, bool transpose = false);

	void set(i32 count, const glm::mat4x3& value, bool transpose = false);
	void set(i32 count, const glm::dmat4x3& value, bool transpose = false);

	template<class T> inline Uniform& operator=(const T& data) { set<T>(data); return *this; }

private:
	friend struct Program;
	Uniform(const Program* program, i32 id);

	glb::GLint id;
	const Program* prog;
};

}}
