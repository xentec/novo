#ifndef SHADER_H
#define SHADER_H

#include "object.h"

namespace novo {
namespace gl {

namespace ShaderType {
	static const GLenum Vertex = GL_VERTEX_SHADER;
	static const GLenum Fragment = GL_FRAGMENT_SHADER;
	static const GLenum Geometry = GL_GEOMETRY_SHADER;
}

class Shader : public Object
{
public:
	Shader(GLenum shader_type, const string& glsl_source = "", bool compile_now = true);
	~Shader();
	void compile(const string& source = "");
	bool isCompiled() const;

	static Shader load(GLenum shader_type, const string& path, bool compile_now = true);
private:
	GLenum type;
	string source;
	bool compiled;

};

}}

#endif // SHADER_H
