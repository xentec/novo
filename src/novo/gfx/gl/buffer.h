#ifndef BUFFER_H
#define BUFFER_H

#include "bindable.h"

#include <vector>

namespace novo {
namespace gl {

namespace BufferType {
	static const GLenum Vertex = GL_ARRAY_BUFFER;
	static const GLenum Data = Vertex;
	static const GLenum Index = GL_ELEMENT_ARRAY_BUFFER;
	static const GLenum Uniform = GL_UNIFORM_BUFFER;
	static const GLenum DrawCommand = GL_DRAW_INDIRECT_BUFFER;
	static const GLenum Shader = GL_SHADER_STORAGE_BUFFER;
	static const GLenum TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER;
}

namespace BufferUsage {
	static const GLenum StaticDraw = GL_STATIC_DRAW;
	static const GLenum StaticRead = GL_STATIC_READ;
	static const GLenum StaticCopy = GL_STATIC_COPY;
	static const GLenum DynamicDraw = GL_DYNAMIC_DRAW;
	static const GLenum DynamicRead = GL_DYNAMIC_READ;
	static const GLenum DynamicCopy = GL_DYNAMIC_COPY;
	static const GLenum StreamDraw = GL_STREAM_DRAW;
	static const GLenum StreamRead = GL_STREAM_READ;
	static const GLenum StreamCopy = GL_STREAM_COPY;
}

namespace BufferAccess {
	static const auto Read = GL_MAP_READ_BIT;
	static const auto Write = GL_MAP_WRITE_BIT;
	static const auto Persistent = GL_MAP_PERSISTENT_BIT;
	static const auto Coherent = GL_MAP_COHERENT_BIT;
	static const auto Unsychronized = GL_MAP_UNSYNCHRONIZED_BIT;
	static const auto FlushExplicit = GL_MAP_FLUSH_EXPLICIT_BIT;
	static const auto InvalidateBuffer = GL_MAP_INVALIDATE_BUFFER_BIT;
	static const auto InvalidateRange = GL_MAP_INVALIDATE_RANGE_BIT;
}

class Buffer : public Bindable
{
public:
	Buffer(GLenum type, GLenum usage);
	~Buffer();

	GLenum getUsage() const;
	void setUsage(GLenum value);

	void allocate(u32 bytes_size);

	// spec
	void setData(u32 bytes_size, const void *data);
	void setSubData(u32 bytes_offset, u32 bytes_size, const void *data);

	void addSubData(u32 bytes_size, const void* data);

	// single structs
	template<typename T>
	void setData(const T& data) { setElements(1, &data); }

	// for arrays
	template<typename T>
	void setElements(u32 size, const T* data) { setData(sizeof(T)*size, data); }

	template<typename T>
	void setSubElements(u32 size, const T* data) { setSubElements(0, size, data); }

	template<typename T>
	void setSubElements(u32 bytes_offset, u32 size, const T* data) { setSubData(bytes_offset, sizeof(T)*size, data); }

	template<typename T>
	void addSubElements(u32 size, const T* data) { addSubData(sizeof(T)*size, data); }

	// for stl container
	template<typename Container>
	void setElements(const Container& data) { setElements(data.size(), &*(data.begin())); }

	template<typename Container>
	void setSubElements(const Container& data) { setSubElements(0, data); }

	template<typename Container>
	void setSubElements(u32 bytes_offset, const Container& data) { setSubElements(bytes_offset, data.size(), &*(data.begin())); }

	template<typename Container>
	void addSubElements(const Container& data) { addSubElements(data.size(), &*(data.begin())); }

	//TODO: MapBuffer
	const void* map(GLenum bitfield);

	u32 size() const;
	u32 offset() const;
private:
	GLenum usage;
	u32 bufSize;
	u32 bufOffset;
};

}}

#endif // BUFFER_H
