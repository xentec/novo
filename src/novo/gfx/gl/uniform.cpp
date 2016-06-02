#include "uniform.h"
#include "program.h"

#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace novo::gl;
using namespace glb;

Uniform::Uniform(const Program* program, i32 id):
	id(id), prog(program)
{}

Uniform::Uniform():
	id(0), prog(nullptr)
{}

Uniform::Uniform(const Uniform& other):
	id(other.id), prog(other.prog)
{}

void Uniform::set(GLsizei count, const f32& value) { glProgramUniform1fv(prog->id, id, count, &value); }
void Uniform::set(GLsizei count, const f64& value) { glProgramUniform1dv(prog->id, id, count, &value); }
void Uniform::set(GLsizei count, const i32& value) { glProgramUniform1iv(prog->id, id, count, &value); }
void Uniform::set(GLsizei count, const u32& value) { glProgramUniform1uiv(prog->id, id, count, &value); }

void Uniform::set(GLsizei count, const vec2& value) { glProgramUniform2fv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const dvec2& value) { glProgramUniform2dv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const ivec2& value) { glProgramUniform2iv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const uvec2& value) { glProgramUniform2uiv(prog->id, id, count, value_ptr(value)); }

void Uniform::set(GLsizei count, const vec3& value) { glProgramUniform3fv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const dvec3& value) { glProgramUniform3dv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const ivec3& value) { glProgramUniform3iv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const uvec3& value) { glProgramUniform3uiv(prog->id, id, count, value_ptr(value)); }

void Uniform::set(GLsizei count, const vec4& value) { glProgramUniform4fv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const dvec4& value) { glProgramUniform4dv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const ivec4& value) { glProgramUniform4iv(prog->id, id, count, value_ptr(value)); }
void Uniform::set(GLsizei count, const uvec4& value) { glProgramUniform4uiv(prog->id, id, count, value_ptr(value)); }


void Uniform::set(GLsizei count, const mat2& value, bool transpose) { glProgramUniformMatrix2fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat2& value, bool transpose) { glProgramUniformMatrix2dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat3& value, bool transpose) { glProgramUniformMatrix3fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat3& value, bool transpose) { glProgramUniformMatrix3dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat4& value, bool transpose) { glProgramUniformMatrix4fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat4& value, bool transpose) { glProgramUniformMatrix4dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }


void Uniform::set(GLsizei count, const mat2x3& value, bool transpose) { glProgramUniformMatrix2x3fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat2x3& value, bool transpose) { glProgramUniformMatrix2x3dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat3x2& value, bool transpose) { glProgramUniformMatrix3x2fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat3x2& value, bool transpose) { glProgramUniformMatrix3x2dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat2x4& value, bool transpose) { glProgramUniformMatrix2x4fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat2x4& value, bool transpose) { glProgramUniformMatrix2x4dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat4x2& value, bool transpose) { glProgramUniformMatrix4x2fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat4x2& value, bool transpose) { glProgramUniformMatrix4x2dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat3x4& value, bool transpose) { glProgramUniformMatrix3x4fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat3x4& value, bool transpose) { glProgramUniformMatrix3x4dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Uniform::set(GLsizei count, const mat4x3& value, bool transpose) { glProgramUniformMatrix4x3fv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Uniform::set(GLsizei count, const dmat4x3& value, bool transpose) { glProgramUniformMatrix4x3dv(prog->id, id, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
