#ifndef BINDABLE_H
#define BINDABLE_H

#include "object.h"

#include <unordered_map>

namespace novo {
namespace gl {

using glGenFuncN = void (*)(GLsizei, GLuint*);
using glDelFuncN = void (*)(GLsizei, const GLuint*);
using glBindFunc = void (*)(GLenum, GLuint);
using glBindFuncS = void (*)(GLuint);

namespace dtl {
	inline GLuint glGen(glGenFuncN glGen)
	{
		GLuint id = 0;
		glGen(1, &id);
		return id;
	}

	template<glDelFuncN F>
	inline void delFunc(GLuint id) { F(1, &id); }

	template<glBindFuncS bind>
	inline void bindFunc(GLenum, GLuint id) { bind(id); }
}

template<GLenum TYPE, glGenFuncN GEN, glDelFuncN DEL, glBindFunc BIND>
class Bindable : public Object<TYPE, dtl::delFunc<DEL> >
{
	typedef Object<TYPE, dtl::delFunc<DEL> > Base;
public:
	void bind() const {
		if(binds[type] == Base::id)
			return;
		BIND(type, Base::id);
		binds[type] = Base::id;
	}

	GLenum getType() const { return type; }

protected:
	Bindable(GLenum type, const string& label = ""):
		Base(dtl::glGen(GEN), label),
		type(type)
	{}

	const GLenum type;

private:
	static std::unordered_map<GLenum, GLuint> binds;
};

template<GLenum TYPE, glGenFuncN GEN, glDelFuncN DEL, glBindFunc BIND>
std::unordered_map<GLenum, GLuint> Bindable<TYPE, GEN, DEL, BIND>::binds;

}}
#endif // BINDABLE_H
