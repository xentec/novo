#include "io.h"

#include <fstream>
#include <stdexcept>

namespace novo {
namespace io {

using std::string;

File::File(const string &path)
{

}

std::vector<u8> File::getData(const std::string &path)
{
	return get<std::vector<u8>>(path);
}
string File::getText(const string &path)
{
	return get<string>(path);
}

template<typename Result>
Result File::get(const string &path)
{
	using ifs = std::ifstream;
	ifs in(path, ifs::binary);
	if (!in.is_open())
		throw std::runtime_error(string("Failed to open \"") + path + string("\""));

	// Thanks to <insane coder> for performance tests
	// http://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html
	Result data;
	in.seekg(0, std::ios::end);
	data.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(reinterpret_cast<char*>(&data[0]), data.size());

	in.close();
	return data;
}

}}

std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
	out << "{"
		<< vec.x << " " << vec.y << " "<< vec.z
		<< "}";

	return out;
}
