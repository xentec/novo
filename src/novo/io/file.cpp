#include "file.h"

#ifdef OS_LINUX
#include <sys/stat.h>
#else
#endif

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

bool File::exists(const std::string& path)
{
#ifdef OS_LINUX
	struct stat info;
	return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFMT) == S_IFREG;
#else
	static_assert(0, "not implemented");
#endif
}

}}
