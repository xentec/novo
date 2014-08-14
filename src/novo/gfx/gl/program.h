#ifndef PROGRAM_H
#define PROGRAM_H

#include "object.h"
#include "shader.h"

namespace novo {
namespace gl {

class Program : public Object
{
public:
	Program();
	Program(Shader& vertex, Shader& fragment, bool link_now = true);
	~Program();

	void attach(Shader shader);
	void link();
	void use();

	// FIXME: Temp solution
	void setFragDataLocation(u32 color_number, const string& name);
private:
	bool linked;
};

}}
#endif // PROGRAM_H
