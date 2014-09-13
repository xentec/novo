#ifndef GL_MESSAGE_CONTROL_H
#define GL_MESSAGE_CONTROL_H

#include "object.h"

#include <vector>

namespace novo {
namespace gl {
namespace debug {

#define GLD(d) gl::GL_DEBUG_##d

namespace Source {
#define S(s) GLD(SOURCE_##s)
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
	GLenum source, type;
	GLuint id;
	bool enabled;
};

inline void messageControl(const MessageState& msg) {
	gl::glDebugMessageControl(msg.source, msg.type, GL_DONT_CARE, 1, &msg.id, static_cast<GLboolean>(msg.enabled));
}

inline void messageControl(GLuint id, bool enabled) {
	gl::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 1, &id, static_cast<GLboolean>(enabled));
}

}}}

#endif // GL_MESSAGE_CONTROL_H
