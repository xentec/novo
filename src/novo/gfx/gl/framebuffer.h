#pragma once

#include "bindable.h"

namespace novo {
namespace gl {

struct Texture;
struct Renderbuffer;

namespace FramebufferType {
#define GL(d) GLenum::GL_##d##_FRAMEBUFFER
	using glb::GLenum;
	static const GLenum
		Default = GLenum::GL_FRAMEBUFFER,
		Draw = GL(DRAW),
		Read = GL(READ);
#undef GL
}

struct Framebuffer : Bindable<glb::GL_FRAMEBUFFER, glb::glGenFramebuffers, glb::glDeleteFramebuffers, glb::glBindFramebuffer>
{
	using Type = glb::GLenum;
	using Status = glb::GLenum;

	Framebuffer(Type type = FramebufferType::Default, const string& label = "");

	void setLabel(const std::string &new_label, bool glLabel = true);

	Status status() const;

	void attach(glb::GLenum component, const Texture& texture, u32 level = 0, u32 zoffset = 0);
	void attach(glb::GLenum component, const Renderbuffer& rbo);

	template<class T>
	inline void attach(u32 color_attachment, const T& t, u32 level = 0, u32 zoffset = 0)
	{
		attach(static_cast<glb::GLenum>(glb::GL_COLOR_ATTACHMENT0 + color_attachment), t, level, zoffset);
	}

	static Framebuffer getDefault(Type type = FramebufferType::Default);
private:
	typedef Bindable<glb::GL_FRAMEBUFFER, glb::glGenFramebuffers, glb::glDeleteFramebuffers, glb::glBindFramebuffer> Base;

	struct DONT {};
	Framebuffer(Type type, DONT);
};

}}
