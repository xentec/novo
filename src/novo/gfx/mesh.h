#pragma once

#include "novo/gfx/drawable.h"
#include "novo/gfx/gl/gl.h"

#include <glm/glm.hpp>

namespace novo {
namespace gfx {

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex;
};

struct Mesh : Drawable
{
	Mesh(string label = "");
	virtual ~Mesh();

	Mesh(const Mesh &);
	Mesh &operator=(const Mesh &);

	Mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices, string label = "");

	void commit();

	void draw(Shader *shader);

	template<class Primitive>
	static Mesh fromPrimitive(const Primitive& p);

private:
	void setupAttributes();

	std::vector<Vertex> vertices;
	std::vector<u32>    indices;

	gl::VertexArray vao;
	gl::Buffer vbo, ibo;
};

template<class Primitive>
Mesh Mesh::fromPrimitive(const Primitive& p)
{
	std::vector<Vertex> vtx(p.indices.size());

	for(usz i = 0; i < vtx.size(); i++)
	{
		Vertex& v = vtx[i];
		v.position = p.vertices[p.indices[i]];
		v.tex = p.texes[i];
	}

	for(usz i = 0; i < vtx.size(); i += 3)
	{
		Vertex  &a = vtx[i],
				&b = vtx[i+1],
				&c = vtx[i+2];

		a.normal = b.normal = c.normal = glm::cross(b.position-a.position, c.position-a.position);
	}

	return Mesh(vtx, std::vector<u32>());
}

}}
