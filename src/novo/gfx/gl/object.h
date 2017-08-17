#pragma once

#include "novo/global.h"
#include "novo/exception.h"

#include <fmt/format.h>

#include <glbinding/Meta.h>
#include <glbinding/gl45core/gl.h>

#include <functional>
#include <unordered_map>

namespace novo {
namespace gl {

#define DBG_GL(type, id, label, op, ref) DBG(4, "{}[{}]({}) {} ({})", glbinding::Meta::getString(type), id, label, op, ref)

namespace glb = ::gl;

using glDelFunc = void (*)(glb::GLuint);
using GLType = glb::GLenum;


template<GLType TYPE, glDelFunc DEL>
struct Object
{
	static const GLType type = TYPE;

	string getLabel() const { return label; }
	void setLabel(const string& new_label, bool glLabel = true)
	{
		label = new_label;
		if(glLabel) labelApply();
	}

	u32 instances() const { return refs[id]; }
	operator glb::GLuint() const { return id; }

protected:
	Object(glb::GLuint id, const string& label = "", bool glLabel = true):
		id(id), label(label)
	{
		if(glLabel) labelApply();
		refs.emplace(id, 1);
		DBG_GL(TYPE, id, label, "created", refs[id]);
	}

	virtual ~Object()
	{
		decrement();
	}

	Object(const Object<TYPE, DEL>& other):
		id(other.id), label(other.label)
	{
		refs[id]++;
		DBG_GL(TYPE, id, label, "copied:C", refs[id]);
	}

	Object<TYPE, DEL>& operator=(const Object<TYPE, DEL>& other)
	{
		decrement();

		id = other.id;
		label = other.label;
		refs[id]++;
		DBG_GL(TYPE, id, label, "copied:A", refs[id]);
		return *this;
	}

	inline void labelApply()
	{
		glb::glObjectLabel(type, id, static_cast<glb::GLsizei>(label.size()), label.c_str());
	}

	const glb::GLuint id;
private:
	string label;
	static std::unordered_map< glb::GLuint, u32> refs;

	void decrement()
	{
		if(--refs[id] == 0) {
			DBG_GL(TYPE, id, label, "deleted", refs[id]);
			refs.erase(id);
			DEL(id);
		} else {
			DBG_GL(TYPE, id, label, "dtored", refs[id]);
		}

	}
};

template< glb::GLenum TYPE, glDelFunc DEL>
std::unordered_map< glb::GLuint, u32> Object<TYPE, DEL>::refs;


struct OpenGLException : Exception
{
public:
	const GLType source;
	const string label;

	template<GLType T, glDelFunc D>
	OpenGLException(const Object<T,D>* obj, const string& reason):
		Exception(fmt::format("{}({}): {}", glbinding::Meta::getString(obj->type), obj->getLabel(), reason)),
		source(obj->type),
		label(obj->getLabel())
	{}
};

namespace Data {
	using Type = glb::GLenum;

	template <class T, Type GLT>
	struct Holder
	{
		Holder(){}
		typedef T type;
		static constexpr usz size() { return sizeof(type); }
		operator Type() const { return GLT; }
	};

	static const Holder<glb::GLbyte,   Type::GL_BYTE>               Byte;
	static const Holder<glb::GLubyte,  Type::GL_UNSIGNED_BYTE>      UByte;
	static const Holder<glb::GLshort,  Type::GL_SHORT>              Short;
	static const Holder<glb::GLushort, Type::GL_UNSIGNED_SHORT>     UShort;
	static const Holder<glb::GLint,    Type::GL_INT>                Int;
	static const Holder<glb::GLuint,   Type::GL_UNSIGNED_INT>       UInt;
	static const Holder<glb::GLint64,  Type::GL_INT64_ARB>          Long;
	static const Holder<glb::GLuint64, Type::GL_UNSIGNED_INT64_ARB> ULong;

	static const Holder<glb::GLfloat,  Type::GL_FLOAT>  Float;
	static const Holder<glb::GLdouble, Type::GL_DOUBLE> Double;

	inline usz sizeOf(Type type)
	{
		switch(type)
		{
		case Type::GL_BYTE:
		case Type::GL_UNSIGNED_BYTE:		return Byte.size();
		case Type::GL_SHORT:
		case Type::GL_UNSIGNED_SHORT:       return Short.size();
		case Type::GL_INT:
		case Type::GL_UNSIGNED_INT:         return Int.size();
		case Type::GL_INT64_ARB:
		case Type::GL_UNSIGNED_INT64_ARB:   return Long.size();
		case Type::GL_FLOAT:                return Float.size();
		case Type::GL_DOUBLE:               return Double.size();
		default:                            return 0;
		}
	}
}






}}
