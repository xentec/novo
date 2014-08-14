#ifndef OBJECT_H
#define OBJECT_H

#include <novo/global.h>

#include <GL/glew.h>

namespace gl {

class Object
{
public:
	string getLabel() const { return label; }
	void setLabel(const string& new_label) { label = new_label; }

	operator GLuint() const { return id; }
protected:
	Object(GLuint gl_id):
		id(gl_id), label("") {}
	const GLuint id;
private:
	string label;
};

}

#endif // OBJECT_H
