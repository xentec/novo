#include "storage.h"

using namespace novo::gl;
using namespace glb;

Storage::Storage(Type type, const string& label):
	Buffer(type, label),
	access(StorageMapAccess::Read)
{}

void Storage::allocate(BufferStorageMask access, u32 bytes_size)
{
	setData(access, bytes_size, nullptr);
}

void Storage::setData(BufferStorageMask access, u32 bytes_size, const void* data)
{
	if(allocated)
		throw OpenGLException(this, "already allocated");

	glBufferStorage(type, bytes_size, data, access);
	this->access = access;
	allocated = true;
}

