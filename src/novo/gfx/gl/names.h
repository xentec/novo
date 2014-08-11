#ifndef NAMES_H
#define NAMES_H

#include <novo/global.h>

#include <GL/glew.h>
#include <map>

namespace gl {
namespace names {

static std::map<GLenum, std::string>
debug {
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
shader {
	{GL_VERTEX_SHADER, "Vertex shader"},
	{GL_FRAGMENT_SHADER, "Fragment shader"},
	{GL_GEOMETRY_SHADER, "Geometry shader"},
},
buffer {
	{GL_ARRAY_BUFFER, "array buffer"},
	{GL_ELEMENT_ARRAY_BUFFER, "index buffer"},
	{GL_UNIFORM_BUFFER, "uniform buffer"},
	{GL_DRAW_INDIRECT_BUFFER, "draw command buffer"},
	{GL_SHADER_STORAGE_BUFFER, "shader storage buffer"},
	{GL_TRANSFORM_FEEDBACK_BUFFER, "tranform feedback buffer"}
};

}}

#endif // NAMES_H
