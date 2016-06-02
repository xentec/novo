#include "mesh.h"

using namespace novo::gfx;
using namespace glm;

Mesh::Mesh(string label):
	Mesh({{}}, {{}}, label)
{}

Mesh::~Mesh()
{}


Mesh::Mesh(const Mesh &rhs):
	vertices(rhs.vertices),	indices(rhs.indices),
	vao(rhs.vao.getLabel()),
	vbo(gl::BufferType::Data, rhs.vbo.getLabel()),
	ibo(gl::BufferType::Index, rhs.ibo.getLabel())
{
	setupAttributes();
}

Mesh &Mesh::operator=(const Mesh &rhs)
{
	return *this;
}


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices, string label):
	vertices(vertices),	indices(indices),
	vao(label+".vao"),
	vbo(gl::BufferType::Data, label+".vbo"),
	ibo(gl::BufferType::Index, label+".ibo")
{
	setupAttributes();
}


void Mesh::commit()
{
	vbo.setElements(gl::BufferUsage::StaticDraw, vertices);
	if(indices.size())
		ibo.setElements(gl::BufferUsage::StaticDraw, indices);
}

void Mesh::draw(Shader* shader)
{
	if(indices.size())
	{
		ibo.bind();
		vao.drawElements(gl::glb::GL_TRIANGLES, indices.size(), gl::Data::UInt);
	} else
	{
		vao.drawArrays(gl::glb::GL_TRIANGLES, vertices.size());
	}
}

void Mesh::setupAttributes()
{
	vao.bindAttribute(vbo, 0, vec3().length(), gl::Data::Float, sizeof(Vertex));
	vao.bindAttribute(vbo, 1, vec3().length(), gl::Data::Float, sizeof(Vertex), offsetof(Vertex, normal));
	vao.bindAttribute(vbo, 2, vec2().length(), gl::Data::Float, sizeof(Vertex), offsetof(Vertex, tex));
}





