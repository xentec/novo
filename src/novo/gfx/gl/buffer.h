#ifndef BUFFER_H
#define BUFFER_H

#include "bindable.h"

#include <vector>

namespace gl {

namespace buffer {
	enum Type : GLenum {
		Vertex = GL_ARRAY_BUFFER,
		Data = Vertex,
		Index = GL_ELEMENT_ARRAY_BUFFER,
		Uniform = GL_UNIFORM_BUFFER,
		DrawCommand = GL_DRAW_INDIRECT_BUFFER,
		Shader = GL_SHADER_STORAGE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
	};

	enum Usage : GLenum {
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,

		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,

		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
	};
}

class Buffer : public Bindable
{
public:
	Buffer(buffer::Type type);
	~Buffer();

	void reserve(u32 bytes_size, buffer::Usage usage);
	void setData(u32 bytes_size, const void *data, buffer::Usage usage);
	void setSubData(u32 bytes_offset, u32 bytes_size, const void *data);

	// single structs
	template<typename T>
	void setData(const T& data, buffer::Usage usage) { setElements(1, &data, usage); }

	// for arrays
	template<typename T>
	void setElements(u32 size, const T* data, buffer::Usage usage) { setData(sizeof(T)*size, static_cast<const void*>(data), usage); }

	template<typename T>
	void setSubElements(u32 bytes_offset, u32 size, const T *data) { setSubData(bytes_offset, sizeof(T)*size, static_cast<const void*>(data)); }

	u32 size();

private:
	Buffer(buffer::Type type, GLuint id);

	buffer::Usage usage;
	buffer::Type type;
	u32 buffer_size;



// Static
public:
	static std::vector<Buffer> generate(buffer::Type type, u32 num, string prefix = "");
};

}

#endif // BUFFER_H
