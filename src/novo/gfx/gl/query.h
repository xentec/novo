#pragma once

#include "bindable.h"

namespace novo {
namespace gl {

namespace QueryType {
	using glb::GLenum;
	static const GLenum
		SamplesPassed                      = GLenum::GL_SAMPLES_PASSED,
		AnySamplesPassed                   = GLenum::GL_ANY_SAMPLES_PASSED,
		AnySamplesPassedConservative       = GLenum::GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
		PrimitivesGenerated                = GLenum::GL_PRIMITIVES_GENERATED,
		TransformFeedbackPrimitivesWritten = GLenum::GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
		TimeElapsed                        = GLenum::GL_TIME_ELAPSED;
}

namespace QueryParameter {
	using glb::GLenum;
#define GL(d) GLenum::GL_QUERY_##d
	static const GLenum
		Result      = GL(RESULT),
		IsAvailable = GL(RESULT_AVAILABLE),
		ResultNow   = GL(RESULT_NO_WAIT);
#undef GL
}


struct Query : Object<glb::GL_QUERY, dtl::delFunc<glb::glDeleteQueries> >
{
	using Type = glb::GLenum;

	Query(Type type, const string& label = "");

	void begin();
	void end();
	void begin(u32 index);
	void end(u32 index);

	void count();

	template<class T>
	T get(Type parameter);

private:
	Type type;
};

}}
