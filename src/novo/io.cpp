#include "io.h"

namespace novo {
namespace io {

std::vector<u8> File::getData(const string &path)
{
	return get<std::vector<u8>>(path);
}

string File::getText(const string &path)
{
	return get<string>(path);
}

}}
