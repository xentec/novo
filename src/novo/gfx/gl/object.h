#ifndef OBJECT_H
#define OBJECT_H

#include <novo/global.h>

#include <GL/glew.h>

class Object
{
public:
	inline operator GLuint() { return id; }
protected:
	Object(GLuint gl_id, const string& label):
		id(gl_id), label(label) {}
	GLuint id;
	string label;
};

#endif // OBJECT_H
