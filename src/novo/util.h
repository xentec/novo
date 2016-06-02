#pragma once

#include "novo/global.h"

template<class Array>
inline usz byteSize(const Array* arr, u32 elements = 1) { return elements * sizeof(Array); }

template<class Container>
inline usz byteSize(const Container& ctr) { return byteSize(ctr.data(), ctr.size()); }

template<class T>
inline ptrS<T> shared(T* obj) { return ptrS<T>(obj); }

template<class Container, class T = typename Container::value_type>
std::vector<T> vectorize(const Container& container) { return std::vector<T>(container.begin(), container.end()); }
