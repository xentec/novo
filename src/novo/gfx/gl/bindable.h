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
	typedef void(*GenFunc)(GLsizei, GLuint*);
	typedef void(*DelFunc)(GLsizei, const GLuint*);
	typedef void(*BindFunc)(GLenum, GLuint);
	typedef void(*BindFuncS)(GLuint);

	Bindable(GenFunc gen, DelFunc del, BindFunc bind, GLenum sub_type);
	Bindable(GenFunc gen, DelFunc del, BindFuncS bind);
	virtual ~Bindable();

	static GLuint glGen(Bindable::GenFunc glGen);

	GLenum type;
private:
	DelFunc glDelete;
	BindFunc glBind;
	BindFuncS glBindS;
};

}}
#endif // BINDABLE_H
