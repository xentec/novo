#include "io.h"

#include <fstream>
#include <stdexcept>

namespace novo {
namespace io {

using std::string;

File::File(const string &path)
{

}

std::vector<u8> File::get(const string &path)
{
	using ifs = std::basic_ifstream<u8>;
	ifs is(path, ifs::in | ifs::binary | ifs::ate);
	if (!is.is_open())
		throw std::runtime_error(string("Failed to open \"") + path + string("\""));

/*	// get length of file:
	i32 length = is.tellg();
	is.seekg(0, is.beg);

	std::vector<u8> data(length);

	// pointer to data
	is.read(reinterpret_cast<uchar>(*data.begin()), length);
	is.close();
*/
    std::vector<u8> data((std::istreambuf_iterator<u8>(is)), (std::istreambuf_iterator<u8>()));

	is.close();
	return data;
}

string File::getText(const string &path)
{
	std::vector<u8> data = get(path);
    return string(data.begin(), data.end());
}

}}

std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
	out << "{"
		<< vec.x << " " << vec.y << " "<< vec.z
		<< "}";

	return out;
}
