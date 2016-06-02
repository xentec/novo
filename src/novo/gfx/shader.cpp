#include "shader.h"

#include "novo/io/file.h"

using namespace novo::gfx;
using namespace novo::gl::glb;

Shader::Shader(const std::string& name):
	prog(name+".prog"), polyMode(GL_FILL)
{
	prog.setFragDataLocation(0, "color");

	if(name.length())
		load(name);
}

void Shader::load(const std::string& name)
{
	string shaderPath = NOVO_SHADER_PATH+name;
	prog.attach(gl::Shader(gl::ShaderType::Vertex, io::File::getText(shaderPath+".v.glsl"), name+".vert"));
	prog.attach(gl::Shader(gl::ShaderType::Fragment, io::File::getText(shaderPath+".f.glsl"), name+".frag"));

	if(io::File::exists(shaderPath+".g.glsl"))
		prog.attach(gl::Shader(gl::ShaderType::Geometry, io::File::getText(shaderPath+".g.glsl"), name+".geom"));
}

void Shader::compile()
{
	for(auto& shader : prog.getShaders())
		shader.second.compile();
	prog.link();
}

void Shader::use() const
{
	using namespace novo::gl::glb;
	glPolygonMode(GL_FRONT_AND_BACK, polyMode);
	prog.use();
}

GLenum Shader::getPolyMode() const
{
	return polyMode;
}

void Shader::setPolyMode(const GLenum& value)
{
	polyMode = value;
}

novo::gl::Uniform Shader::operator[](string name)
{
	return prog.getUniform(name);
}
