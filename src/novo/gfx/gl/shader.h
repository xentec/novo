#ifndef SHADER_H
#define SHADER_H

#include "object.h"

namespace gl {

namespace shader {
	enum Type {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
	};
}

class Shader : public Object
{
public:
	Shader(shader::Type type, const string& glsl_source = "", bool compile_now = true);
	~Shader();
	void compile(const string& source = "");
	bool isCompiled() const;

	static Shader load(shader::Type type, const string& path, bool compile_now = true);
private:
	shader::Type type;
	string source;
	bool compiled;

};

}

#endif // SHADER_H
