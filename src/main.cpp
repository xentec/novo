
#include "novo/app.h"

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <exception>
#include <iostream>
#include <iterator>
#include <vector>


using fmt::print;

int main(int argc, char* argv[])
{
//	cxxopts::Options opts(argv[0], " - forever in development");
//		("s,size", "space size", cxxopts::value<u32>()->default_value("16"))
//		("h,help", "print help")

	try {
		return novo::App().run();
	} catch (const novo::Exception& e) {
		print(std::cerr, "Something went wrong!\n");
		print(std::cerr, "Novo: {}\n", e.reason);
		return 2;
	}
}
