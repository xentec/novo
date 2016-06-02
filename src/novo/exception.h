#pragma once

#include "novo/global.h"

#include <exception>

namespace novo {

class Exception : public std::exception {
public:
	Exception(const string& reason = ""):
		std::exception(),
		reason(reason)
	{}

	virtual const char* what() const noexcept {
		return typeid(this).name();
	}

	const string reason;
};

}
