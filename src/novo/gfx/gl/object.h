#ifndef OBJECT_H
#define OBJECT_H

#include <novo/global.h>

#include <glbinding/gl/gl.h>

#include <functional>
#include <unordered_map>

namespace novo {
namespace gl {

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

class Object
{
public:
	string getLabel() const { return label; }
	void setLabel(const string& new_label) { label = new_label; }

	u32 instances() const { return refs[id]; }

	operator GLuint() const { return id; }
protected:
	typedef std::function<void(GLuint)> DelFunc;
	typedef std::function<void(const GLuint*)> DelFuncP;

	Object(GLuint gl_id, DelFunc func);
	Object(GLuint gl_id, DelFuncP func);
	Object(const Object& other);
	virtual ~Object();

	const GLuint id;
private:
	string label;
	DelFunc glDel;

	static std::unordered_map<GLuint, u32> refs;
};

namespace dtl {

template <GLenum N>
struct TypeSize
{
	enum { size =
		   (N == DataType::HalfFloat)	? sizeof(f32)/2 :
		   (N == DataType::Float)		? sizeof(f32) :
		   (N == DataType::Double)		? sizeof(f64) :

		   (N == DataType::Int  || N == DataType::UInt)		? sizeof(i32) :
		   (N == DataType::Short|| N == DataType::UShort)	? sizeof(i16) : sizeof(i8)
		 };
};

}

}}

#endif // OBJECT_H
