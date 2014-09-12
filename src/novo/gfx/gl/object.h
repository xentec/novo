#ifndef OBJECT_H
#define OBJECT_H

#include <novo/global.h>

#include <boost/format.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/Meta.h>

#include <functional>
#include <unordered_map>

namespace novo {
namespace gl {


namespace dtl {
#if DEBUG > 5
	static boost::format dbg("%s[%d] '%s' %s (%d)");
	#define DBG_GL(type,misc) DBG((dtl::dbg % glbinding::Meta::getString(type) % misc))
#else
	#define DBG_GL(type,misc)
#endif
}


using namespace ::gl;

struct DrawElementsIndrectCommand {
	GLuint
		count,
		instanceCount,
		firstIndex,
		baseVertex,
		baseInstance;
};

namespace DataType {
	static const GLenum Byte = GL_BYTE;
	static const GLenum UByte = GL_UNSIGNED_BYTE;
	static const GLenum Short = GL_SHORT;
	static const GLenum UShort = GL_UNSIGNED_SHORT;
	static const GLenum Int = GL_INT;
	static const GLenum UInt = GL_UNSIGNED_INT;

	static const GLenum HalfFloat = GL_HALF_FLOAT;
	static const GLenum Float = GL_FLOAT;
	static const GLenum Double = GL_DOUBLE;
}

using glDelFunc = void (*)(GLuint);

template<GLenum TYPE, glDelFunc DEL>
class Object
{
public:
	string getLabel() const { return label; }
	void setLabel(const string& new_label) { label = new_label; }

	u32 instances() const { return refs[id]; }

	operator GLuint() const { return id; }
protected:
	Object(GLuint gl_id, const string& label = ""):
		id(gl_id), label(label)
	{
		refs.emplace(id, 1);
		DBG_GL(TYPE, id % label % "created" % refs[id]);
	}

	Object(const Object<TYPE, DEL>& other):
		id(other.id), label(other.label)
	{
		refs[id]++;
		DBG_GL(TYPE, id % label % "copied" % refs[id]);
	}

	virtual ~Object()
	{
		DBG_GL(TYPE, id % label % "dtored" % refs[id]);
		if(--refs[id] == 0) {
			DEL(id);
			refs.erase(id);
			DBG_GL(TYPE, id % label % "deleted" % refs[id]);
		}
	}

	const GLuint id;
private:
	string label;
	static std::unordered_map<GLuint, u32> refs;
};

template<GLenum TYPE, glDelFunc DEL>
std::unordered_map<GLuint, u32> Object<TYPE, DEL>::refs;

}}

#endif // OBJECT_H
