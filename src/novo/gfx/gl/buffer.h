#pragma once

#include "bindable.h"

#include "novo/util.h"

namespace novo {
namespace gl {

namespace BufferType {
	using glb::GLenum;
	static const GLenum
		Vertex            = GLenum::GL_ARRAY_BUFFER,
		Data              = Vertex,
		Element           = GLenum::GL_ELEMENT_ARRAY_BUFFER,
		Index             = Element,
		Uniform           = GLenum::GL_UNIFORM_BUFFER,
		DrawCommand       = GLenum::GL_DRAW_INDIRECT_BUFFER,
		Shader            = GLenum::GL_SHADER_STORAGE_BUFFER,
		TransformFeedback = GLenum::GL_TRANSFORM_FEEDBACK_BUFFER;
}

namespace BufferUsage {
	using glb::GLenum;
	static const GLenum
		StaticDraw = GLenum::GL_STATIC_DRAW,
		StaticRead = GLenum::GL_STATIC_READ,
		StaticCopy = GLenum::GL_STATIC_COPY,
		DynamicDraw = GLenum::GL_DYNAMIC_DRAW,
		DynamicRead = GLenum::GL_DYNAMIC_READ,
		DynamicCopy = GLenum::GL_DYNAMIC_COPY,
		StreamDraw = GLenum::GL_STREAM_DRAW,
		StreamRead = GLenum::GL_STREAM_READ,
		StreamCopy = GLenum::GL_STREAM_COPY;
}
namespace BufferMapRangeAccess {
#define GL(d) glb::GL_MAP_##d##_BIT
	static const auto
		Read = GL(READ),
		Write = GL(WRITE),
		Persistent = GL(PERSISTENT),
		Coherent = GL(COHERENT);
	static const auto
		Unsychronized = GL(UNSYNCHRONIZED),
		FlushExplicit = GL(FLUSH_EXPLICIT),
		InvalidateBuffer = GL(INVALIDATE_BUFFER),
		InvalidateRange = GL(INVALIDATE_RANGE);
#undef GL
}

struct Buffer : Bindable<glb::GL_BUFFER, glb::glGenBuffers, glb::glDeleteBuffers, glb::glBindBuffer>
{
	using Usage = glb::GLenum;
	using Type = glb::GLenum;

	Buffer(Type type, const string& label = "");

	Usage getUsage() const;

	void allocate(Usage usage, usz bytes_size);

	// spec
	void setData(Usage buffer_usage, usz bytes_size, const void *data);
	void setSubData(usz bytes_offset, usz bytes_size, const void *data);

	void addSubData(usz bytes_size, const void* data);

	// single structs
	template<class T>
	void setData(Usage usage, const T& data) { setData(usage, byteSize(&data), &data); }

	// for stl container
	template<class Container, class... Args>
	void allocateElements(Usage usage, const Container& data, const Args&... args) { allocate(usage, byteSize(data), args...); }

	template<class Container>
	void setElements(Usage usage, const Container& data) { setData(usage, byteSize(data), &*(data.begin())); }

	template<class Container>
	void setSubElements(usz bytes_offset, const Container& data) { setSubData(bytes_offset, byteSize(data), &*(data.begin())); }

	template<class Container>
	void addSubElements(const Container& data) { addSubData(byteSize(data), &*(data.begin())); }

	//TODO: MapBuffer
	const void* map(glb::GLenum access);
	const void* mapRange(usz bytes_size, usz offset, glb::BufferAccessMask access);

	usz size() const;
	usz offset() const;
private:
	Usage usage;
	usz bufSize;
	usz bufOffset;

	// Madness
	template<class Container, class... Args>
	void allocate(Usage usage, u32 bytes_size, const Container& ctr, const Args&... args) { allocate(usage, byteSize(ctr) + bytes_size, args...); }
};

}}
