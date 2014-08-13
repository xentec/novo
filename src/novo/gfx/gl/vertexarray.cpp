#include "vertexarray.h"

using namespace gl;

VertexArray::VertexArray():
	Bindable(Bindable::VertexArray,
			 glGenVertexArrays,
			 glDeleteVertexArrays,
			 glBindVertexArray)
{
}
