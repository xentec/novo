#ifndef BUFFER_H
#define BUFFER_H

#include "object.h"

#include <vector>

namespace gl {

class Buffer : public Object
{
public:
	enum Type : GLenum {
		Vertex = GL_ARRAY_BUFFER,
		Data = Vertex,
		Index = GL_ELEMENT_ARRAY_BUFFER,
		Uniform = GL_UNIFORM_BUFFER,
		DrawCommand = GL_DRAW_INDIRECT_BUFFER,
		Shader = GL_SHADER_STORAGE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	};


	Buffer(Buffer::Type type, string name = "");
	~Buffer();

	void bind();


	static std::vector<Buffer> generate(Buffer::Type type, u32 num, string prefix = "");
private:
	Buffer(Type t, const string &name, GLuint id);

	Buffer::Type type;
};

}

#endif // BUFFER_H
