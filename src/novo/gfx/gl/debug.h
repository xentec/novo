#pragma once

#include "object.h"

#include <vector>

namespace novo {
namespace gl {
namespace debug {

#define GLD(d) glb::GL_DEBUG_##d

namespace Source {
#define S(s) GLD(SOURCE_##s)
	using glb::GLenum;
	static const GLenum
		API = S(API),
		WindowSystem = S(WINDOW_SYSTEM),
		ShaderCompiler = S(SHADER_COMPILER),
		ThirdParty = S(THIRD_PARTY),
		Application = S(APPLICATION),
		Other = S(OTHER);
#undef S
}

namespace Type {
#define S(s) GLD(TYPE_##s)
	using glb::GLenum;
	static const GLenum
		Error = S(ERROR),
		Deprecated = S(DEPRECATED_BEHAVIOR),
		Undefined = S(UNDEFINED_BEHAVIOR),
		Portability = S(PORTABILITY),
		Performance = S(PERFORMANCE),
		Marker = S(MARKER),
		Other = S(OTHER);
#undef S
}

namespace Severity {
#define S(s) GLD(SEVERITY_##s)
	using glb::GLenum;
	static const GLenum
		High = S(HIGH),
		Medium = S(MEDIUM),
		Low = S(LOW),
		Notification = S(NOTIFICATION),
		Info = Notification;
#undef S
}

#undef GLD

struct MessageState {
	GLType source;
	glb::GLenum type;
	u32 id;
	bool enabled;
};

inline void messageControl(const MessageState& msg) {
	glb::glDebugMessageControl(msg.source, msg.type, glb::GL_DONT_CARE, 1, &msg.id, static_cast<glb::GLboolean>(msg.enabled));
}

}}}
