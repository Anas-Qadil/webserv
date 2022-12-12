#include "./parse.config.hpp"
#include <unistd.h>

std::vector<Config> descentParser() 
{
	std::vector<Config> servers;
	std::cout << "Descent parser" << std::endl;
	return (servers);
}

void loadingConfig() 
{
	// std::cout << "Loading config" << std::endl;
	size_t i = 0;
	while (i < 10) {
		std::cout << "...........";
		i++;
		usleep(100000);
		std::cout.flush();
	}
	std::cout << std::endl;
}