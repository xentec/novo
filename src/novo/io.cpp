#include "io.h"

#include <fstream>
#include <stdexcept>

namespace novo {
namespace util {

using std::string;

string loadFile(const string& file_name) {
	using std::ifstream;

	string content;
	ifstream is(file_name, ifstream::in | ifstream::binary | ifstream::ate);
	if (!is.is_open())
		throw std::runtime_error(string("Failed to open \"") + file_name + string("\""));

	// get length of file:
	i32 length = is.tellg();
	is.seekg(0, is.beg);

	content.resize(length, ' ');

	// pointer to string data
	is.read(&*content.begin(), length);
	is.close();

	return content;
}

}
}

std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
	out << "{"
		<< vec.x << " " << vec.y << " "<< vec.z
		<< "}";

	return out;
}
