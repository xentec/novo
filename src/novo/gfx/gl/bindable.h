#ifndef BINDABLE_H
#define BINDABLE_H

#include "object.h"

#include <unordered_map>

namespace gl {

class Bindable : public Object {
public:
	void bind();
protected:
	enum ObjType {
		Buffer,
		Texture,
		Sampler,
		VertexArray,
		Framebuffer,
		Renderbuffer,
	};

	typedef void(*GenFunc)(GLsizei, GLuint*);
	typedef void(*DelFunc)(GLsizei, const GLuint*);
	typedef void(*BindFunc)(GLenum, GLuint);
	typedef void(*BindFuncS)(GLuint);

	Bindable(ObjType obj_type, GenFunc gen, DelFunc del, BindFunc bind, GLenum sub_type);
	Bindable(ObjType obj_type, GenFunc gen, DelFunc del, BindFuncS bind);
	virtual ~Bindable();

	static GLuint glGen(Bindable::GenFunc glGen);

	GLenum subType;
private:
	ObjType type;

	DelFunc glDelete;
	BindFunc glBind;
	BindFuncS glBindS;
};

}
#endif // BINDABLE_H
