#ifndef IO_H
#define IO_H

#include <novo/global.h>
#include <novo/exception.h>

#include <fstream>
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

class FileException : public novo::NovoException {
public:
	const string path;
	FileException(string path, string reason):
		NovoException(string("File ")+reason+string(": ")+path),
		path(path)
	{}
};

// File definitions
// #################
template<typename Result>
Result File::get(const string &path)
{
	using ifs = std::ifstream;
	ifs in(path, ifs::binary);
	if (!in.is_open())
		throw FileException(path, "not accessible");

	// Thanks to <insane coder> for performance tests
	// http://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html
	Result data;
	in.seekg(0, std::ios::end);
	data.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	// TODO: non array version
	in.read(reinterpret_cast<char*>(&data[0]), data.size());

	in.close();
	return data;
}

}}

#endif // IO_H
