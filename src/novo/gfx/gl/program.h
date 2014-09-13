#ifndef PROGRAM_H
#define PROGRAM_H

#include "object.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

namespace novo {
namespace gl {

using namespace glm;

typedef GLint Attribute;
typedef GLint Uniform;

class Program : public Object<GL_PROGRAM, glDeleteProgram>
{
public:
	Program(const string& label = "");
	Program(Shader& vertex, Shader& fragment, bool link_now = true);

	Shader getShader(GLenum shader_type);

	void attach(const Shader& shader);
	void detach(const Shader& shader);
	void detach(GLenum shader_type);
	void link();
	void use();

	void bindFragDataLocation(u32 color_number, const string& name);

	Attribute getAttribute(const string& name) const;
	Uniform getUniform(const string& name) const;

	template<typename T>
	void setUniform(const string name, const T& value) { setUniform(getUniform(name), value); }

	template<typename T>
	void setUniform(Uniform location, const T& value) { setUniform(location, 1, value); }


	template<typename T>
	void setUniform(const string name, GLsizei count, const T& value) { setUniform(getUniform(name), count, value); }

	void setUniform(Uniform location, GLsizei count, const GLfloat& value) ;
	void setUniform(Uniform location, GLsizei count, const GLdouble& value);
	void setUniform(Uniform location, GLsizei count, const GLint& value);
	void setUniform(Uniform location, GLsizei count, const GLuint& value);

	void setUniform(Uniform location, GLsizei count, const vec2& value);
	void setUniform(Uniform location, GLsizei count, const dvec2& value);
	void setUniform(Uniform location, GLsizei count, const ivec2& value);
	void setUniform(Uniform location, GLsizei count, const uvec2& value);

	void setUniform(Uniform location, GLsizei count, const vec3& value);
	void setUniform(Uniform location, GLsizei count, const dvec3& value);
	void setUniform(Uniform location, GLsizei count, const ivec3& value);
	void setUniform(Uniform location, GLsizei count, const uvec3& value);

	void setUniform(Uniform location, GLsizei count, const vec4& value);
	void setUniform(Uniform location, GLsizei count, const dvec4& value);
	void setUniform(Uniform location, GLsizei count, const ivec4& value);
	void setUniform(Uniform location, GLsizei count, const uvec4& value);


	void setUniform(Uniform location, GLsizei count, const mat2& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat2& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat3& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat3& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat4& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat4& value, bool transpose = false);


	void setUniform(Uniform location, GLsizei count, const mat2x3& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat2x3& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat3x2& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat3x2& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat2x4& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat2x4& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat4x2& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat4x2& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat3x4& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat3x4& value, bool transpose = false);

	void setUniform(Uniform location, GLsizei count, const mat4x3& value, bool transpose = false);
	void setUniform(Uniform location, GLsizei count, const dmat4x3& value, bool transpose = false);

private:
	bool linked;

	std::unordered_map<GLenum, Shader> shaders;
};

}}
#endif // PROGRAM_H
