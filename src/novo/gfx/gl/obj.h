#ifndef GRAPHICS_UTIL_H
#define GRAPHICS_UTIL_H

#include <novo/global.h>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>
#include <stdexcept>


namespace glm {
	typedef detail::tvec4<uint8, highp>		ubvec4;
}

namespace novo {
namespace graphics {

struct DrawElementsIndrectCommand {
	GLuint
		count,
		instanceCount,
		firstIndex,
		baseVertex,
		baseInstance;
};

namespace util {

using std::string;

GLuint createShader(GLenum type, const string& source);
GLuint createProgram(GLint vertexShader, GLint fragmentShader, GLint geometryShader = -1);
GLuint createProgram(const string& vertexSource, const string& fragmentSource, const string& geometrySource = "");
GLuint createProgramFromFiles(const string& vertexPath, const string& fragmentPath, const string& geometryPath = "");



}}}


#endif // GRAPHICS_UTIL_H
