#ifndef BINDABLE_H
#define BINDABLE_H

#include "object.h"

#include <unordered_map>

namespace gl {

class Bindable : public Object {
public:
	void bind();
protected:
	enum ObjType : GLenum {
		Buffer,
		Texture,
		Sampler,
		VertexArray,
		Framebuffer,
		Renderbuffer,
	};

	typedef void(*BindFunc)(GLenum, GLuint);
	typedef void(*BindFuncS)(GLuint);

	Bindable(GLuint id, ObjType obj_type, BindFunc bind, GLenum sub_type);
	Bindable(GLuint id, ObjType obj_type, BindFuncS bind);

	GLenum subType;
private:
	ObjType type;

	BindFunc glBind;
	BindFuncS glBindS;

	static std::unordered_map<GLenum, GLuint> bindings;
};

}
#endif // BINDABLE_H
