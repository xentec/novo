#ifndef BUFFER_H
#define BUFFER_H

#include "bindable.h"

#include <novo/util.h>

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

namespace BufferMapRangeAccess {
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

	GLenum getUsage() const;
	void setUsage(GLenum value);

	void allocate(u32 bytes_size);

	// spec
	void setData(u32 bytes_size, const void *data);
	void setSubData(u32 bytes_offset, u32 bytes_size, const void *data);

	void addSubData(u32 bytes_size, const void* data);

	// single structs
	template<typename T>
	void setData(const T& data) { setData(byteSize(&data), &data); }

	// for stl container
	template<typename Container, typename... Args>
	void allocateElements(const Container& ctr, const Args&... args) { allocate(byteSize(ctr), args...); }

	template<typename Container>
	void setElements(const Container& data) { setData(byteSize(data), &*(data.begin())); }

	template<typename Container>
	void setSubElements(u32 bytes_offset, const Container& data) { setSubData(bytes_offset, byteSize(data), &*(data.begin())); }

	template<typename Container>
	void addSubElements(const Container& data) { addSubData(byteSize(data), &*(data.begin())); }

	//TODO: MapBuffer
	const void* map(GLenum access);
	const void* mapRange(u32 bytes_size, u32 offset, BufferAccessMask access);

	u32 size() const;
	u32 offset() const;
private:
	GLenum usage;
	u32 bufSize;
	u32 bufOffset;

	// Madness
	template<typename Container, typename... Args>
	void allocate(u32 bytes_size, const Container& ctr, const Args&... args) { allocate(byteSize(ctr) + bytes_size, args...); }
};

}}

#endif // BUFFER_H
