#pragma once

#include "novo/global.h"
#include "novo/exception.h"

#include <fstream>
#include <type_traits>
#include <vector>

namespace novo {
namespace io {

using std::enable_if;
using std::is_pod;
using std::is_pointer;

struct File {
	static std::vector<u8> getData(const string& path);
	static string getText(const string &path);

	template<class Result,
			 typename enable_if<
				 is_pod<Result>::value &&
				 !is_pointer<Result>::value
			 >::type* = nullptr>
	static Result get(const string &path);

	template<class Result,
			 typename enable_if<!is_pod<Result>::value>::type* = nullptr>
	static Result get(const string &path);

	template<class Result,
			 typename enable_if<is_pointer<Result>::value>::type* = nullptr>
	static void get(const string &path, Result data, usz size);

	static bool exists(const string& path);
};

// TODO: http://en.cppreference.com/w/cpp/io/ios_base/iostate

class FileException : public novo::Exception {
public:
	FileException(string path, string reason):
		Exception(string("File ")+reason+string(": ")+path),
		path(path), reason(reason)
	{}

	const string path;
	const string reason;
};

// File definitions
// #################

// Thanks to <insane coder> for performance tests
// http://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html

template<class Result, typename enable_if<is_pod<Result>::value && !is_pointer<Result>::value>::type*>
Result File::get(const string &path)
{
	std::ifstream in(path, std::ios::binary | std::ios::ate);
	if (!in.is_open())
		throw FileException(path, "not accessible");

	Result data;
	usz size = std::min(sizeof(data), static_cast<usz>(in.tellg()));

	in.seekg(0, std::ios::beg);
	in.read(reinterpret_cast<char*>(&data), size);
	in.close();

	return data;
}

template<class Result, typename enable_if<!is_pod<Result>::value>::type*>
Result File::get(const string &path)
{
	std::ifstream in(path, std::ios::binary | std::ios::ate);
	if (!in.is_open())
		throw FileException(path, "not accessible");

	Result data;
	data.resize(in.tellg());

	in.seekg(0, std::ios::beg);
	in.read(reinterpret_cast<char*>(&data[0]), data.size());
	in.close();

	return data;
}


template<class Result, typename enable_if<is_pointer<Result>::value>::type*>
void File::get(const string &path, Result data, usz size)
{
	std::ifstream in(path, std::ios::binary | std::ios::ate);
	if (!in.is_open())
		throw FileException(path, "not accessible");

	if(size > in.tellg())
		size = in.tellg();

	in.seekg(0, std::ios::beg);
	in.read(reinterpret_cast<char*>(data), size);
	in.close();
}

}}
