#ifndef GLOBAL_H
#define GLOBAL_H

#include "config.h"

#include <string>
#include <memory>
#include <cstdint>

#ifdef DEBUG
    #include<iostream>
#endif

// chars
typedef unsigned char	uchar;

// integer
typedef int8_t		i8;
typedef uint8_t		u8;

typedef int16_t		i16;
typedef uint16_t	u16;

typedef int32_t		i32;
typedef uint32_t	u32;

typedef int64_t		i64;
typedef uint64_t	u64;

// decimals
typedef float		f32;
typedef double		f64;

//
template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using uptr = std::unique_ptr<T>;
template<typename T>
using wptr = std::weak_ptr<T>;

using std::string;

#endif // GLOBAL_H
