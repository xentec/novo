#ifndef IO_H
#define IO_H

#include <novo/global.h>

#include <glm/glm.hpp>

#include <vector>

namespace novo {
namespace io {

using std::string;

class File {
public:
	File(const string& path);

	template<typename Result>
	static Result get(const string &path);
	static std::vector<u8> getData(const string& path);
	static string getText(const string &path);
};


string loadFile(const string& file_name);

}}

std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec);


#endif // IO_H
