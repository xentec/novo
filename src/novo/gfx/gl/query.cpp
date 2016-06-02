#include "query.h"

using namespace novo::gl;
using namespace glb;


Query::Query(Type type, const string& label):
	Object(dtl::genFunc<glGenQueries>(), label, false),
	type(type)
{}

void Query::begin()
{
	glBeginQuery(type,id);
	labelApply();
}

void Query::end()
{
	glEndQuery(type);
}

void Query::begin(u32 index)
{
	glBeginQueryIndexed(type, index, id);
	labelApply();
}

void Query::end(u32 index)
{
	glEndQueryIndexed(type, index);
}

void Query::count()
{
	//if(type == QueryType::TimeElapsed)
	glQueryCounter(id, GL_TIMESTAMP);
}

namespace novo {
namespace gl {

template<>
i32 Query::get<i32>(GLenum request_type) {
	i32 ret;
	glGetQueryObjectiv(id, request_type, &ret);
	return ret;
}
template<>
u32 Query::get<u32>(GLenum request_type) {
	u32 ret;
	glGetQueryObjectuiv(id, request_type, &ret);
	return ret;
}
template<>
i64 Query::get<i64>(GLenum request_type) {
	i64 ret;
	glGetQueryObjecti64v(id, request_type, &ret);
	return ret;
}
template<>
u64 Query::get<u64>(GLenum request_type) {
	u64 ret;
	glGetQueryObjectui64v(id, request_type, &ret);
	return ret;
}

}}
