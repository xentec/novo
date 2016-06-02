
#include "novo/app.h"

#include <cppformat/format.h>
#include <cxxopts.hpp>

#include <exception>
#include <iostream>
#include <iterator>
#include <vector>


using fmt::print;

int main(int argc, char* argv[])
{
	cxxopts::Options opts(argv[0], " - forever in development");
	opts.add_options()
		("s,size", "space size", cxxopts::value<u32>()->default_value("16"))
		("h,help", "print help")
	;
	opts.parse(argc, argv);

	if(opts.count("help"))
	{
		fmt::print(opts.help());
		return 0;
	}
	try {
		return novo::App(opts).run();
	} catch (const novo::Exception& e) {
		print(std::cerr, "Something went wrong!\n");
		print(std::cerr, "Novo: {}\n", e.reason);
		return 2;
	}
}
