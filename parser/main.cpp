#include <iostream>
#include "./modules/descent-parser/parse.config.hpp"

int main(void) {
	try {
		descentParser();
	} catch (std::exception &e) {
		std::cout << e.what() /* the actual fuck */ << std::endl;
	}
}