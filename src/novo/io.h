#ifndef IO_H
#define IO_H

#include <novo/global.h>

#include <glm/glm.hpp>

namespace novo {
namespace util {

string loadFile(const string& file_name);

}
}

std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec);


#endif // IO_H
