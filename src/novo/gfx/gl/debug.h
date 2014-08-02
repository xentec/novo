#ifndef ERROR_H
#define ERROR_H

#include <novo/global.h>

#include <GL/glew.h>
#include <map>

static struct glString {
	std::map<GLenum, std::string> Debug {
	   // Source
	   {GL_DEBUG_SOURCE_API, "API"},
	   {GL_DEBUG_SOURCE_WINDOW_SYSTEM, "Window System"},
	   {GL_DEBUG_SOURCE_SHADER_COMPILER, "Shader Compiler"},
	   {GL_DEBUG_SOURCE_THIRD_PARTY, "Third Party"},
	   {GL_DEBUG_SOURCE_APPLICATION, "Application"},
	   {GL_DEBUG_SOURCE_OTHER, "Other"},
	   // Type
	   {GL_DEBUG_TYPE_ERROR, "Error"},
	   {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated"},
	   {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined"},
	   {GL_DEBUG_TYPE_PORTABILITY, "Portability"},
	   {GL_DEBUG_TYPE_PERFORMANCE, "Performance"},
	   {GL_DEBUG_TYPE_OTHER, "Other"},
	   {GL_DEBUG_TYPE_MARKER, "Marker"},
	   // Severity
	   {GL_DEBUG_SEVERITY_HIGH, "High"},
	   {GL_DEBUG_SEVERITY_MEDIUM, "Medium"},
	   {GL_DEBUG_SEVERITY_LOW, "Low"},
	   {GL_DEBUG_SEVERITY_NOTIFICATION, "Notify"},
	},
	Shader {
	   {GL_VERTEX_SHADER, "Vertex shader"},
	   {GL_FRAGMENT_SHADER, "Fragment shader"},
	   {GL_GEOMETRY_SHADER, "Geometry shader"},
	},
	Buffer {
	   {GL_ARRAY_BUFFER, "Array buffer"},
	   {GL_ELEMENT_ARRAY_BUFFER, "Element array buffer"},
	   {GL_DRAW_INDIRECT_BUFFER, "Draw indirect buffer"},
	};

} GL;

#endif // ERROR_H
