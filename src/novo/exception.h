#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <novo/global.h>

#include <exception>

namespace novo {

class NovoException : public std::exception {
	string msg;
public:
	NovoException(string reason):
		std::exception(),
		msg(reason)
	{}

	const string getReason() const {
		return msg;
	}

	virtual const char* what() const noexcept {
		return typeid(this).name();
	}
};

}

#endif // EXCEPTIONS_H
