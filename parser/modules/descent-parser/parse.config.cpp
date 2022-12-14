#include "./parse.config.hpp"
#include "../utils/utils.hpp"
#include <unistd.h>

std::vector<Config> descentParser(const std::string path) 
{
	std::vector<Config> servers;
	std::vector<std::string> serversData;
	
	std::string content = readFile(path);
	analyze(content);
	serversData = grapServers(content);

	// print serversData
	for (size_t i = 0; i < serversData.size(); i++) {
		Config server = parseServer(serversData[i]);
	}


	return (servers);
}

const std::vector<std::string> grapServers(std::string &content) {
	std::vector<std::string> servers;
	while (1) {
		std::string serverData = getServer(content);
		if (serverData.length() == 0) break ;
		servers.push_back(serverData);
	}
	return (servers);
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

const Config parseServer(std::string &serverContent) {
	Config server = Config();
	std::vector<int> ports;
	std::string line;
	size_t i = 0;
	std::string location;

	// get Location
	location = serverContent.substr(serverContent.find("location\n{"), serverContent.length());
	// remove location
	serverContent.erase(serverContent.find("location\n{"), serverContent.length());

	parseServerContent(serverContent, server);
	parseLocationContent(location, server);
	return (server);
}

std::string getLine(std::string &content) {
	std::string line;

	size_t i = 0;
	while (i < content.length()) {
		if (content[i] == '\n') {
			line = content.substr(0, i);
			analyzeLine(line);
			content.erase(0, i + 1);
			break ;
		}
		i++;
	}
	return (line);
}
std::vector<int> getPorts(std::string line) {
	std::vector<int> ports;
	std::string port;
	size_t i = 0;

	if (line.size() == 0) throw std::runtime_error("Error: No port found");

	while (i < line.length()) {
		if (line[i] == ' ' && port != "") {
			if (!isPortNumber(port)) throw std::runtime_error("Error: Port number is not valid");
			ports.push_back(std::stoi(port));
			port = "";
		} else {
			port += line[i];
		}
		i++;
	}
	if (!isPortNumber(port)) throw std::runtime_error("Error: Port number is not valid");
	ports.push_back(std::stoi(port));
	return (ports);
}

// function to check if a string of numbers is a valid port number
bool isPortNumber(std::string port) {
	try {
		port.erase(0, port.find_first_not_of(' '));
		port.erase(port.find_last_not_of(' ') + 1);
		if (port.size() == 0) return (false);
		for (size_t i = 0; i < port.size(); i++) {
			if (port[i] < '0' || port[i] > '9') return (false);
		}
		// check if port number is greater than 0 and less than 65535
		if (std::stoi(port) < 0 || std::stoi(port) > 65535) return (false);
		return (true);
	} catch (std::exception &e) {
		return (false);
	}
}

void analyzeLine(std::string &line) {
	if (line.length() == 0) return ;
	// check if line ends with ';'
	if (line[line.length() - 1] != ';') throw std::runtime_error("Error: Line does not end with ';'");
	if (line.find("listen") != std::string::npos) {
		// check if listen is followed by a space and a number
		if (line[line.find("listen") + 6] != ' ') throw std::runtime_error("Error: Ports and listen are not separated by a space");
		if (line[line.find("listen") + 7] < '0' || line[line.find("listen") + 7] > '9') throw std::runtime_error("Error: Port number is not valid");
		// remove ";"
		line.erase(line.length() - 1, 1);
	} else  
	if (line.find("server_name") != std::string::npos) {
		// check if server_name is followed by a space and a string
		if (line[line.find("server_name") + 11] != ' ') throw std::runtime_error("Error: Server name and server_name are not separated by a space");
		if (line[line.find("server_name") + 12] == ' ') throw std::runtime_error("Error: Server name is empty");
		// remove ";"
		line.erase(line.length() - 1, 1);
	}
	if (line.find("root") != std::string::npos) {
		// check if root is followed by a space and a string
		if (line[line.find("root") + 4] != ' ') throw std::runtime_error("Error: Root path and root are not separated by a space");
		if (line[line.find("root") + 5] == ' ') throw std::runtime_error("Error: Root path is empty");
		// remove ";"
		line.erase(line.length() - 1, 1);
	}
	if (line.find("host") != std::string::npos) {
		// check if index is followed by a space and a string
		if (line[line.find("host") + 4] != ' ') throw std::runtime_error("Error: Index and index are not separated by a space");
		if (line[line.find("host") + 5] == ' ') throw std::runtime_error("Error: Index is empty");
		// remove ";"
		line.erase(line.length() - 1, 1);
	}
	if (line.find("client_max_body_size") != std::string::npos) {
		// check if client_max_body_size is followed by a space and a string
		if (line[line.find("client_max_body_size") + 20] != ' ') throw std::runtime_error("Error: Client max body size and client_max_body_size are not separated by a space");
		if (line[line.find("client_max_body_size") + 21] == ' ') throw std::runtime_error("Error: Client max body size is empty");
		// remove ";"
		line.erase(line.length() - 1, 1);
	}
}

// this functio to check if the server content is valid and change it if needed
void analyzeServerContent(std::string &content) {
	if (content.length() == 0) throw std::runtime_error("Error: No server content found");
	if (content[0] ==  '\n') content.erase(0, 1);
	// check if listen, server_name, root, host, client_max_body_size are present
	if (content.find("listen") == std::string::npos) throw std::runtime_error("Error: No port found");
	if (content.find("server_name") == std::string::npos) throw std::runtime_error("Error: No server name found");
	if (content.find("root") == std::string::npos) throw std::runtime_error("Error: No root path found");
	if (content.find("host") == std::string::npos) throw std::runtime_error("Error: No host found");
	if (content.find("client_max_body_size") == std::string::npos) throw std::runtime_error("Error: No client max body size found");
}

void parseServerContent(std::string &content, Config &server) {
	std::string line;
	// check if server content is valid
	analyzeServerContent(content);
	// split content into lines
	std::cout << content << std::endl;
	std::cout << " ------------------ " << std::endl;
	for (size_t i = 0; i < content.length(); i++) {
		line = getLine(content);
		if (line.length() == 0) continue ;
		if (line.find("listen") != std::string::npos) {
			std::vector<int> ports = getPorts(line.substr(line.find("listen") + 7));
			server.setPort(ports);
		} else if (line.find("server_name") != std::string::npos) {
			std::vector<std::string> serverNames = getServerNames(line.substr(line.find("server_name") + 12));
			server.setServerName(serverNames);
			// print server names
			for (size_t i = 0; i < serverNames.size(); i++) {
				std::cout << serverNames[i] << std::endl;
			}
		}
		// parse the next element in th file tomorrow here ====>
	}
}

void parseLocationContent(std::string &content, Config &location) {

}

std::vector<std::string> getServerNames(std::string serverNames) {
	std::vector<std::string> names;
	std::string name;
	// split server names into vector
	for (size_t i = 0; i < serverNames.length(); i++) {
		if (serverNames[i] == ' ') {
			names.push_back(name);
			name = "";
		} else {
			name += serverNames[i];
		}
	}
	names.push_back(name);
	analyzeServerNames(names);
	return (names);
}

// a function to check if a vector of server names are valid
void analyzeServerNames(std::vector<std::string> serverNames) {
	if (!analyzeRepeatedElements(serverNames)) throw std::runtime_error("Error: Repeated server names");
	// check if server names are valid (only letters, numbers, points, underscore, and hyphens)
	for (size_t i = 0; i < serverNames.size(); i++) {
		for (size_t j = 0; j < serverNames[i].length(); j++) {
			if (!isalnum(serverNames[i][j]) && serverNames[i][j] != '.' && serverNames[i][j] != '_' && serverNames[i][j] != '-') throw std::runtime_error("Error: Invalid server name");
		}
	}
}

// a function to check if a vector of strings have repeated elements
bool analyzeRepeatedElements(std::vector<std::string> elements) {
	for (size_t i = 0; i < elements.size(); i++) {
		for (size_t j = i + 1; j < elements.size(); j++) {
			if (elements[i] == elements[j]) return (false);
		}
	}
	return (true);
}