#include "./parse.config.hpp"
#include "../utils/utils.hpp"
#include <unistd.h>

std::vector<Config> descentParser(const std::string path) 
{
	std::vector<Config> servers;
	std::string content = readFile(path);
	analyze(content);
	// grep servers from content
	grapServers(content);
	std::cout << content << std::endl;
	return (servers);
}

const std::vector<std::string> grapServers(std::string &content) {
	std::cout << getServer(content) << std::endl;
	std::cout << "------------------------" << std::endl;
	return std::vector<std::string>();
}

// return content when all open brackets are closed
std::string getServer(std::string &content) {
	std::string formatedContent;
	size_t i = 0;
	size_t openBrackets = 1; // 1 because we already found "server\n{"
	size_t closeBrackets = 0;

	// find "server\n{" and remove it
	content.erase(0, content.find("server\n{") + 8);
	while (i < content.length()) {
		if (content[i] == '{') openBrackets++;
		if (content[i] == '}') closeBrackets++;
		if (openBrackets == closeBrackets && openBrackets != 0) {
			formatedContent += content.substr(0, i + 1);
			content.erase(0, i + 1);
			// if last character is '}' remove it
			if (formatedContent[formatedContent.length() - 1] == '}') 
				formatedContent.erase(formatedContent.length() - 1, 1);
			break ;
		}
		i++;
	}
	return (formatedContent);
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