#pragma once

#include "bindable.h"

namespace novo {
namespace gl {

namespace TextureType {
	using glb::GLenum;
#define GL(d) GLenum::GL_TEXTURE_##d
	static const GLenum
		S1D = GL(1D),
		S2D = GL(2D),
		S3D = GL(3D),

		A1D = GL(1D_ARRAY),
		A2D = GL(2D_ARRAY),

		CubeMap = GL(CUBE_MAP),
		CubeMapArray = GL(CUBE_MAP_ARRAY),

		Rectangle = GL(RECTANGLE);
#undef GL
}

struct Texture : Bindable<glb::GL_TEXTURE, glb::glGenTextures, glb::glDeleteTextures, glb::glBindTexture>
{
	using Type = glb::GLenum;
	using Format = glb::GLenum;
	using FormatInternal = glb::GLenum;
	using Parameter = glb::GLenum;

	Texture(Type type, const string& label = "");

	static void activate(glb::GLenum num);
	static inline void activate(u32 num = 0) { activate(static_cast<glb::GLenum>(glb::GL_TEXTURE0 + num)); }

	void setData(i32 level, FormatInternal iformat, u32 width,                        i32 border, Format format, Data::Type data_type, const void* data);
	void setData(i32 level, FormatInternal iformat, u32 width, u32 height,            i32 border, Format format, Data::Type data_type, const void* data);
	void setData(i32 level, FormatInternal iformat, u32 width, u32 height, u32 depth, i32 border, Format format, Data::Type data_type, const void* data);

	void setParameter(Parameter name, glb::GLenum value);
	inline void setParameter(Parameter name, i32 value) { setParameter(name, static_cast<glb::GLenum>(value)); }

	void generateMipmap();
};

}}
