#include "texture.h"

using namespace novo::gl;
using namespace glb;


Texture::Texture(GLenum type, const string& label):
	Bindable<GL_TEXTURE, glGenTextures, glDeleteTextures, glBindTexture>(type, label)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(GL_CLAMP_TO_BORDER));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(GL_CLAMP_TO_BORDER));
}

void Texture::activate(GLenum num)
{
	glActiveTexture(num);
}

void Texture::setData(i32 level, FormatInternal iformat, u32 width, i32 border, Format format, Data::Type data_type, const void* data)
{
	bind();
	glTexImage1D(type, level, static_cast<GLint>(iformat),
				 width,
				 border, format, data_type, data);
}

void Texture::setData(i32 level, FormatInternal iformat, u32 width, u32 height, i32 border, Format format, Data::Type data_type, const void* data)
{
	bind();
	glTexImage2D(type, level, static_cast<GLint>(iformat),
				 width, height,
				 border, format, data_type, data);
}

void Texture::setData(i32 level, FormatInternal iformat, u32 width, u32 height, u32 depth, i32 border, Format format, Data::Type data_type, const void* data)
{
	bind();
	glTexImage3D(type, level, static_cast<GLint>(iformat),
				 width, height, depth,
				 border, format, data_type, data);
}

void Texture::setParameter(GLenum name, GLenum value)
{
	bind();
	glTexParameteri(type, name, static_cast<GLint>(value));
}

void Texture::generateMipmap()
{
	bind();
	glGenerateMipmap(type);
}

// TODO: Implement
