#pragma once

#include "object.h"

#include <unordered_map>

namespace novo {
namespace gl {

using glGenFuncN = void (*)(glb::GLsizei, glb::GLuint*);
using glDelFuncN = void (*)(glb::GLsizei, const glb::GLuint*);
using glBindFunc = void (*)(glb::GLenum, glb::GLuint);
using glBindFuncS = void (*)(glb::GLuint);

namespace dtl {
	template<glGenFuncN F>	inline glb::GLuint genFunc()                      { glb::GLuint id = 0; F(1, &id); return id; }
	template<glDelFuncN F> 	inline void delFunc(glb::GLuint id)               { F(1, &id); }
	template<glBindFuncS F>	inline void bindFunc(glb::GLenum, glb::GLuint id) { F(id); }
}

template<GLType GLT, glGenFuncN GEN, glDelFuncN DEL, glBindFunc BIND>
struct Bindable : Object<GLT, dtl::delFunc<DEL>>
{
	using Base = Object<GLT, dtl::delFunc<DEL>>;
	using Type = glb::GLenum;

	void bind() const {
		if(binds[type] == Base::id)
			return;
		BIND(type, Base::id);
		binds[type] = Base::id;
	}

	void unbind() const {
		if(binds[type] == Base::id)
			bind0();
	}

	inline
	void bind0() const {
		bind0(type);
	}

	static void bind0(Type type) {
		BIND(type, 0);
		binds[type] = 0;
	}

	Type getType() const { return type; }
protected:
	Bindable(Type type, const string& label = ""):
		Bindable(dtl::genFunc<GEN>(), type, label)
	{}

	Bindable(glb::GLuint id, Type type, const string& label = ""):
		Base(id, label, false),
		type(type)
	{
		bind(); // WA: error when setting label on certain objects before binding
		if(label.size())
			Base::setLabel(label);
	}

	const Type type;

private:
	static std::unordered_map<Type, glb::GLuint> binds;
};

template<GLType GLT, glGenFuncN GEN, glDelFuncN DEL, glBindFunc BIND>
std::unordered_map<typename Bindable<GLT, GEN, DEL, BIND>::Type, glb::GLuint> Bindable<GLT, GEN, DEL, BIND>::binds;

}}
