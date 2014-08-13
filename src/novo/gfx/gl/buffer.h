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

	enum Access : GLenum {
		Read = GL_MAP_READ_BIT,
		Write = GL_MAP_WRITE_BIT,
		Persistent = GL_MAP_PERSISTENT_BIT,
		Coherent = GL_MAP_COHERENT_BIT,
		Unsychronized = GL_MAP_UNSYNCHRONIZED_BIT,
		FlushExplicit = GL_MAP_FLUSH_EXPLICIT_BIT,
		InvalidateBuffer = GL_MAP_INVALIDATE_BUFFER_BIT,
		InvalidateRange = GL_MAP_INVALIDATE_RANGE_BIT,
	};
}

class Buffer : public Bindable
{
public:
	Buffer(buffer::Type type, buffer::Usage usage);
	~Buffer();

	buffer::Usage getUsage() const;
	void setUsage(const buffer::Usage &value);

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
	const void* map(buffer::Access bitfield);

	u32 size() const;
	u32 offset() const;
private:
	buffer::Usage usage;
	buffer::Type type;
	u32 bufSize;
	u32 bufOffset;
};

}

#endif // BUFFER_H
