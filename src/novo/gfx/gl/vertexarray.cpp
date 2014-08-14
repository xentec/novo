#include "vertexarray.h"

using namespace novo::gl;

VertexArray::VertexArray():
	Bindable(glGenVertexArrays,
			 glDeleteVertexArrays,
			 glBindVertexArray)
{
}
