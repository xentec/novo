#pragma once

#include "config.h"

#include <string>
#include <memory>
#include <cinttypes>

// (more) chars
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

// pointer size dependent
typedef std::ptrdiff_t  isz;
typedef std::size_t     usz;


// pointer wrapper
template<class T>
using ptrS = std::shared_ptr<T>;
template<class T>
using ptrU = std::unique_ptr<T>;
template<class T>
using ptrW = std::weak_ptr<T>;

// always needed
using std::string;


#ifdef DEBUG
	#include <fmt/format.h>

	template<class... Args>
	inline void _dbg(const std::string_view &format, const Args& ... args)
	{
		fmt::print(format, args...);
		fmt::print("\n");
	}

	template<class... Args>
	inline void _dbg(i8 lvl, const std::string_view &format, const Args& ... args)
	{
		if(lvl <= DEBUG)
			_dbg(format, args...);
	}

	template<class... Args> // cond is u8 because bool is 'ambiguous'
	inline void _dbg(i8 lvl, u8 cond, const std::string_view &format, const Args& ... args)
	{
		if(cond)
			_dbg(lvl, format, args...);
	}

	#define DBG(...) _dbg(__VA_ARGS__);
	#define DBG_(...) _dbg_(__VA_ARGS__)
#else
	#define DBG(...)
	#define DBG_(...)
#endif
