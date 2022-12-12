#include <iostream>
#include "./modules/descent-parser/parse.config.hpp"
#include "./modules/utils/utils.hpp"

int main(int argc, char **argv) {
	try {
		if (argc != 2) {
			throw std::runtime_error("Usage: ./parser <config file>");
		}
		std::string content = readFile(argv[1]);
		analyze(content);
		// loadingConfig();
		std::cout << content << std::endl;
		// grapServers(content);
	} catch (std::exception &e) {
		std::cout << e.what() /* the actual fuck */ << std::endl;
	}
}