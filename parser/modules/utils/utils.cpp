
#include "utils.hpp"

const std::vector<std::string> grapServers(std::string content) {
	std::cout << content << std::endl;

	return std::vector<std::string>();
}

const std::string readFile(std::string path) {
	std::ifstream file(path);
	std::string line;
	std::string content;
	while (std::getline(file, line)) {
		content += line;
		content.push_back('\n');
	}
	return (content);
}