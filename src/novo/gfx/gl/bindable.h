#ifndef BINDABLE_H
#define BINDABLE_H

#include "object.h"

#include <unordered_map>

namespace novo {
namespace gl {

class Bindable : public Object {
public:
	void bind();
protected:
	typedef void(*GenFuncN)(GLsizei, GLuint*);
	typedef void(*DelFuncN)(GLsizei, const GLuint*);
	typedef void(*BindFunc)(GLenum, GLuint);
	typedef void(*BindFuncS)(GLuint);

	Bindable(GenFuncN gen, DelFuncN del, BindFunc bind, GLenum sub_type);
	Bindable(GenFuncN gen, DelFuncN del, BindFuncS bind);

	static GLuint glGen(Bindable::GenFuncN glGen);

	GLenum type;
private:
	DelFuncN glDelete;
	BindFunc glBind;
	BindFuncS glBindS;
};

}}
#endif // BINDABLE_H
