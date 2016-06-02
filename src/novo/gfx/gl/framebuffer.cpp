#include "framebuffer.h"

#include "texture.h"
#include "renderbuffer.h"

using namespace novo::gl;
using namespace glb;

Framebuffer::Framebuffer(Type type, const string& label):
	Bindable<GL_FRAMEBUFFER, glGenFramebuffers, glDeleteFramebuffers, glBindFramebuffer>(type, label)
{}

void Framebuffer::setLabel(const std::string& new_label, bool glLabel)
{
	if(id)
		Base::setLabel(new_label, glLabel);
}

Framebuffer::Status Framebuffer::status() const
{
	bind();
	return glCheckFramebufferStatus(type);
}

void Framebuffer::attach(GLenum component, const Texture& texture, u32 level, u32 zoffset)
{
	bind();
	switch(texture.getType()) {
	case TextureType::S1D:
		glFramebufferTexture1D(type, component, texture.getType(), texture, level);
		break;
	case TextureType::S2D:
		glFramebufferTexture2D(type, component, texture.getType(), texture, level);
		break;
	case TextureType::S3D:
		glFramebufferTexture3D(type, component, texture.getType(), texture, level, zoffset);
		break;
	default:
		glFramebufferTexture(type, component, texture, level);

	}
}

void Framebuffer::attach(GLenum component, const Renderbuffer& rbo)
{
	bind();
	glFramebufferRenderbuffer(type, component, rbo.getType(), rbo);
}

Framebuffer Framebuffer::getDefault(Type type)
{
	return Framebuffer(type, DONT());
}

Framebuffer::Framebuffer(Type type, DONT):
	Bindable<GL_FRAMEBUFFER, glGenFramebuffers, glDeleteFramebuffers, glBindFramebuffer>
	(0, type)
{}


// TODO: Implement
