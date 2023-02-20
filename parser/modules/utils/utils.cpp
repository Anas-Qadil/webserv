/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:18:48 by aqadil            #+#    #+#             */
/*   Updated: 2023/01/08 10:18:49 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "utils.hpp"

const std::string readFile(std::string path) {
	std::ifstream file(path);
	std::string line;
	std::string content;

	while (std::getline(file, line)) {
		formatLine(line);
		if (line.length() <= 0) 
			continue;
		content += line;
		// peek returns the next character in the input sequence without extracting it
		if (file.peek() == EOF) break; 
		content.push_back('\n');
	}
	generaleCheck(content);
	generaleFormat(content);
	return (content);
}

void formatLine(std::string &line) {
	std::string newLine;
	// trim left
	line.erase(0, line.find_first_not_of(" \t"));
	// trim right
	line.erase(line.find_last_not_of(" \t") + 1);
	// replace tabs with spaces
	for (size_t i = 0; i < line.length(); i++)
		if (line[i] == '\t') line[i] = ' ';
	// replace multiple spaces with one
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == ' ' && line[i + 1] == ' ') {
			line.erase(i, 1);
			i--;
		}
	}
	// remove nginx file comments
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == '#') {
			line.erase(i, line.length() - i);
			break;
		}
	}
	// if line starts with { remove it and add { to the previous line
	if (line[0] == '{' && line.length() > 1) {
		line.erase(0, 1);
		line.insert(0, "{\n");
	}
	// if line ends with { remove it and add { to the next line
	if (line[line.length() - 1] == '{' && line.length() > 1) {
		// check if there is space before the {
		if (line[line.length() - 2] == ' ') line.erase(line.length() - 2, 1);
		line.erase(line.length() - 1, 1);
		line.push_back('\n');
		line.push_back('{');
	}
}

void analyze(std::string &content) {
	std::string formatedContent;

	if (checkBrackets(content) != 0)
		throw std::runtime_error("Error: Brackets are not balanced");
	// get first 6 characters form the content
	std::string first6 = content.substr(0, 6);
	// check if the first 6 characters are "http\n"
	if (first6 != "http\n{")
		throw std::runtime_error("Error: config file must start with \"http\n{\"");
	// check if the last 2 characters are "};"
	if (content[content.length() - 2] != '}' || content[content.length() - 1] != ';')
		throw std::runtime_error("Error: config file must end with \"};\"");
	// check if there is a server block
	if (content.find("server\n{") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one server block");
	// check if there is a location block
	if (content.find("location /\n{") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one location block for default root \"/\"");
	// check if there is a root directive
	if (content.find("root") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one root directive");
	// check if there is a listen directive
	if (content.find("listen") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one listen directive");
	// check if there is a host directive
	if (content.find("host") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one host directive");
	// check if there is a server_name directive
	if (content.find("server_name") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one server_name directive");
	// check if there is a client_max_body_size directive
	if (content.find("client_max_body_size") == std::string::npos)
		throw std::runtime_error("Error: config file must have at least one client_max_body_size directive");
	// remove "http\n{" from the content
	content.erase(0, 6);
	if (content[0] == '\n') content.erase(0, 1);
	// remove "};\n" from the content
	content.erase(content.length() - 3, 3);
	// if u rememberd any test case add it here :) ===>
	// .....
}

// check if all open brackets have a closing bracket
int checkBrackets(std::string content) {
	int openBrackets = 0;
	int closeBrackets = 0;
	for (size_t i = 0; i < content.length(); i++) {
		if (content[i] == '{') {
			openBrackets++;
		} else if (content[i] == '}') {
			closeBrackets++;
		}
	}
	if (openBrackets != closeBrackets) {
		return (1);
	}
	return (0);
}

void generaleCheck(std::string content) {
	// check for "location " without a "/" after it
	if (content.find("location ") != std::string::npos) {
		size_t pos = content.find("location ");
		while (pos != std::string::npos) {
			if (content[pos + 9] != '/') {
				throw std::runtime_error("Error: location must be followed by a \"/\"");
			}
			pos = content.find("location ", pos + 1);
		}
	}
}

void generaleFormat(std::string &content) {
	// check if ';' not followed by a '\n' and add '\n' if needed
	for (size_t i = 0; i < content.length(); i++) {
		if (content[i] == ';' && content[i + 1] != '\0' ) {
			if (content[i + 1] != '\n') {
				content.insert(i + 1, "\n");
			}
		}
	}
	// std::cout << content << std::endl;
}