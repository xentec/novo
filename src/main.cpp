#include <novo/novo.h>

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {

	// Declare the supported options.
	po::options_description desc("Options");
	desc.add_options()
		("help", "help message")
	;

	po::variables_map opts;
	po::store(po::parse_command_line(argc, argv, desc), opts);
	po::notify(opts);

	if (opts.count("help")) {
		std::cout << desc << std::endl;
		return 0;
	}

	try {
		return Novo(opts).run();
	} catch (const NovoException& e) {
		// TODO: better errors
		std::cerr << "Novo: " << e.what() << std::endl;
		return 2;
	} catch (const std::exception& e) {
		std::cerr << "Fatal: " << e.what() << std::endl;
		return 1;
	}
}

