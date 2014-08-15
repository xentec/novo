#ifndef UTIL_H
#define UTIL_H

#include <novo/global.h>

template<typename Array>
inline std::size_t byteSize(const Array* arr, u32 elements = 1) { return elements * sizeof(Array); }

template<typename Container>
inline std::size_t byteSize(const Container& ctr) { return byteSize(ctr.data(), ctr.size()); }

#endif // UTIL_H
