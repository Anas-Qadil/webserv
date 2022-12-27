#include <iostream>
#include "./modules/descent-parser/parse.config.hpp"
#include "./modules/utils/utils.hpp"

int main(int argc, char **argv) {
	try {
		std::string config = "./config/nginx.conf";
		if (argc > 2)
			throw std::runtime_error("Usage: ./parser <config file>");
		else if (argc == 2)
			config = argv[1];
		descentParser(config);
	} catch (std::exception &e) {
		std::cout << e.what() /* the actual fuck */ << std::endl;
	}
}