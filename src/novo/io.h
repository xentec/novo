#ifndef IO_H
#define IO_H

#include <novo/global.h>
#include <vector>

namespace novo {
namespace io {

class File {
public:

	template<typename Result>
	static Result get(const string &path);
	static std::vector<u8> getData(const string& path);
	static string getText(const string &path);
};

}}

#endif // IO_H
