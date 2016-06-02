#pragma once

#include "buffer.h"

namespace novo {
namespace gl {

namespace StorageType = BufferType;
namespace StorageMapAccess = BufferMapRangeAccess;

struct Storage : Buffer
{
	using Type = Buffer::Type;

	Storage(Type type, const string& label = "");

	void allocate(glb::BufferStorageMask access, u32 bytes_size);
	void setData(glb::BufferStorageMask access, u32 bytes_size, const void *data);
	void setSubData(u32 bytes_offset, u32 bytes_size, const void *data);

	template<class T>
	inline
	void setData(glb::BufferStorageMask access, const T& data) { setData(access, byteSize(&data), &data); }

	// for stl container
	template<class Container, class... Args>
	inline
	void allocateElements(glb::BufferStorageMask access, const Container& ctr, const Args&... args) { allocate(access, byteSize(ctr), args...); }

	template<class Container>
	inline
	void setElements(glb::BufferStorageMask access, const Container& data) { setData(access, byteSize(data), &*(data.begin())); }

private:
	glb::BufferStorageMask access;
	bool allocated;
};

}}
