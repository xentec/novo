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


}}

#endif // OBJECT_H
