#include "./parse.config.hpp"

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
		servers.push_back(server);
	}
	// print servers
	for (size_t i = 0; i < servers.size(); i++) {
		servers[i].print();
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
	if (serverContent.find("location /\n{") == std::string::npos)
		throw std::runtime_error("Error: wrong location formate");
	location = serverContent.substr(serverContent.find("location /\n{"), serverContent.length());
	// remove location
	serverContent.erase(serverContent.find("location /\n{"), serverContent.length());
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
	// std::cout << content << std::endl;
	// std::cout << "-----------------------------------------" << std::endl;
	for (size_t i = 0; i < content.length(); i++) {
		line = getLine(content);
		if (line.length() == 0) continue ;
		if (line.find("listen") != std::string::npos) {
			std::vector<int> ports = getPorts(line.substr(line.find("listen") + 7));
			server.setPort(ports);
		} else if (line.find("server_name") != std::string::npos) {
			std::vector<std::string> serverNames = getServerNames(line.substr(line.find("server_name") + 12));
			server.setServerName(serverNames);
		} else if (line.find("host") != std::string::npos) {
			std::string hostname = getHostname(line.substr(line.find("host") + 5));
			server.setHost(hostname);
		} else if (line.find("client_max_body_size") != std::string::npos) {
			int clientMaxBodySize = getClientMaxBodySize(line.substr(line.find("client_max_body_size") + 21));
			server.setClientMaxBodySize(clientMaxBodySize);
		} else if (line.find("root") != std::string::npos) {
			std::string root = getServerRoot(line.substr(line.find("root") + 5));
			server.setRoot(root);
		}
	}
}

void parseLocationContent(std::string &content, Config &server) {
	// std::cout << content << std::endl;
	// std::cout << "-----------------------------------------" << std::endl;
	std::vector<std::string> locations;
	while (content.find("}\nlocation /") != std::string::npos) {
		locations.push_back(content.substr(0, content.find("}\nlocation /")));
		content.erase(0, content.find("}\nlocation /") + 2);
	}

	locations.push_back(content.substr(0, content.find("}\n")));
	content.erase(0, content.find("}\n") + 2);

	// loop through locations vector and print each location
	for (size_t i = 0; i < locations.size(); i++ ) {
		analyzeLocationContent(locations[i], server);
	}
}

std::string getLocationLine(std::string &content) {
	std::string line;
	size_t i = 0;
	while (content[i] != '\n') {
		line += content[i];
		i++;
	}
	content.erase(0, i + 1);
	return (line);
}

void analyzeLocationContent(std::string location, Config &server) {
	std::string line;
	std::map<std::string, Location> loca;
	std::string path;

	for (size_t i = 0; i < location.length(); i++) {
		// get line
		line = getLocationLine(location);
		if (line.length() == 0) continue;
		if (line.find("location") != std::string::npos) {
			path = getLocationPath(line.substr(line.find("location") + 9));
			loca[path] = Location();	
		} else if (line.find("autoindex") != std::string::npos) {
			std::string autoindex = getAutoindex(line.substr(line.find("autoindex") + 10));
			loca[path].setAutoindex(autoindex);
		} else if (line.find("index") != std::string::npos) {
			std::string index = getIndex(line.substr(line.find("index")  + 6));
			loca[path].setIndex(index);
		} else if (line.find("root") != std::string::npos) {
			std::string root = getLocationRoot(line.substr(line.find("root") + 5));
			loca[path].setRoot(root);
		} else if (line.find("upload_enable") != std::string::npos) {
			std::string uploadEnable = getUploadEnable(line.substr(line.find("upload_enable") + 14));
			loca[path].setUploadEnable(uploadEnable);
		} else if (line.find("upload_path") != std::string::npos) {
			std::string uploadPath = getUploadPath(line.substr(line.find("upload_path") + 12));
			loca[path].setUploadPath(uploadPath);
		} else if (line.find("allowed_methods") != std::string::npos) {
			std::vector<std::string> allowedMethods = getAllowedMethods(line.substr(line.find("allowed_methods") + 16));
			loca[path].setAllowedMethods(allowedMethods);
		}
	}
	server.setLocation(path, loca[path]);
}

std::vector<std::string> getAllowedMethods(std::string str) {
	std::vector<std::string> allowedMethods;
	std::string method;
	// check for valid braces
	if (!hasValidBraces(str)) throw std::runtime_error("Error: Invalid braces in allowed_methods");
	// remove ; at the end
	if (str[str.length() - 1] == ';') str.erase(str.length() - 1, 1);
	// remove braces
	str.erase(0, 1);
	str.erase(str.length() - 1, 1);
	// check if string hasother characters than spaces and commas and normal characters
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ' ' && str[i] != ',' && !isalpha(str[i])) throw std::runtime_error("Error: Invalid characters in allowed_methods");
	}

	// split string by comma
	while (str.find(",") != std::string::npos) {
		method = str.substr(0, str.find(","));
		// remove spaces
		while (method.find(" ") != std::string::npos) {
			method.erase(method.find(" "), 1);
		}
		allowedMethods.push_back(method);
		str.erase(0, str.find(",") + 1);
	}
	// remove spaces
	while (str.find(" ") != std::string::npos) {
		str.erase(str.find(" "), 1);
	}
	allowedMethods.push_back(str);

	// check if allowed methods are valid [GET, POST, DELETE]
	for (size_t i = 0; i < allowedMethods.size(); i++) {
		if (allowedMethods[i] != "GET" && allowedMethods[i] != "POST" && allowedMethods[i] != "DELETE") throw std::runtime_error("Error: Invalid method in allowed_methods");
	}
	return (allowedMethods);
}

std::string getUploadPath(std::string str) {
	// remove ; at the end
	if (str[str.length() - 1] == ';') str.erase(str.length() - 1, 1);
	if (str.length() == 0) throw std::runtime_error("Error: No upload_path found");
	// validate file path
	if (!isValidFilePath(str)) throw std::runtime_error("Error: Invalid upload_path");
	return (str);
}

std::string getUploadEnable(std::string str) {
	// remove ; at the end
	if (str[str.length() - 1] == ';') str.erase(str.length() - 1, 1);
	if (str.length() == 0) throw std::runtime_error("Error: No upload_enable found");
	if (str != "on" && str != "off") throw std::runtime_error("Error: Invalid upload_enable");
	return (str);
}

std::string getLocationRoot(std::string root) {
	// check if root is valid
	// remove ; at the end
	if (root[root.length() - 1] == ';') root.erase(root.length() - 1, 1);
	if (root.length() == 0) throw std::runtime_error("Error: No root path found");
	// validate file path
	if (!isValidFilePath(root)) throw std::runtime_error("Error: Invalid root path");
	return (root);
}

std::string getIndex(std::string filePath) {
	// check if index is valid
	// remove ; at the end
	if (filePath[filePath.length() - 1] == ';') filePath.erase(filePath.length() - 1, 1);
	if (filePath.length() == 0) throw std::runtime_error("Error: No index found");
	// validate file path
	if (!isValidFilePath(filePath)) throw std::runtime_error("Error: Invalid index");
	return (filePath);
}

std::string getLocationPath(std::string path) {
	// check if path is valid
	if (path.length() == 0) throw std::runtime_error("Error: No location path found");
	if (!isValidUrlPath(path)) throw std::runtime_error("Error: Invalid location path");
	return (path);
}

std::string getAutoindex(std::string autoindex) {
	//remove ; at the end
	if (autoindex[autoindex.length() - 1] == ';') autoindex.erase(autoindex.length() - 1, 1);
	// check if autoindex is valid
	if (autoindex.length() == 0) throw std::runtime_error("Error: No autoindex found");
	if (autoindex != "on" && autoindex != "off") throw std::runtime_error("Error: Invalid autoindex");
	return (autoindex);
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

void analyzeHostname(std::string &hostname) {
	// validate hostname here ======>
}

std::string getHostname(std::string line) {
	std::string hostname = line;
	analyzeHostname(hostname);
	return (hostname);
}

void analyzeClientMaxBodySize(std::string &clientMaxBodySize) {
	// validate client max body size here ======>
}

void analyzeServerRoot(std::string &serverRoot) {
	// validate server root here ======>
}

int getClientMaxBodySize(std::string line) {
	try {
		analyzeClientMaxBodySize(line);
		int clientMaxBodySize = 0;
		// check if client max body size is a number
		for (size_t i = 0; i < line.length(); i++) {
			if (!isdigit(line[i])) throw std::runtime_error("Error: Client max body size is not a number");
		}
		clientMaxBodySize = std::stoi(line);
		// check if client max body size is valid
		if (clientMaxBodySize < 0) throw std::runtime_error("Error: Client max body size is negative");
		return (clientMaxBodySize);
	} catch (std::exception &e) {
		throw std::runtime_error("Error: Client max body size is not a valid number");
	}
}

std::string getServerRoot(std::string line) {
	std::string root = line;
	analyzeServerRoot(root);
	// check if root is valid
	if (root.length() == 0) throw std::runtime_error("Error: No root path found");
	if (root[0] == ' ') root.erase(0, 1);
	if (root[root.length() - 1] == ' ') root.erase(root.length() - 1, 1);
	if (root[root.length() - 1] != '/') root += '/';
	return (root);
}

bool isValidUrlPath(const std::string& path) {
  // A valid URL path must start with a '/' character
  if (path[0] != '/') {
    return false;
  }

  // Iterate through each character in the path
  for (size_t i = 1; i < path.length(); i++) {
    char c = path[i];
    // A valid URL path can only contain alphanumeric characters, underscores, and hyphens
    if (!isalnum(c) && c != '_' && c != '-') {
      return false;
    }
  }

  return true;
}


bool isValidFilePath(const std::string &path) {
  // A valid file path must start with a '/' or a letter
  if (path[0] != '/' && !isalpha(path[0])) {
    return false;
  }
  // Iterate through each character in the path
  for (size_t i = 1; i < path.length(); i++) {
    char c = path[i];
    if (!isalnum(c) && c != '_' && c != '-' && c != '.' && c != '/') {
      return false;
    }
  }
  return (true);
}

bool hasValidBraces(const std::string& str) {
	std::stack<char> s;
	size_t i = 0;

	while (i < str.length()) {
		char c = str[i];
		if (c == '(' || c == '[' || c == '{') {
				s.push(c);
		} else if (c == ')') {
			if (s.empty() || s.top() != '(') {
					return false;
			}
			s.pop();
		} else if (c == ']') {
			if (s.empty() || s.top() != '[') {
					return false;
			}
			s.pop();
		} else if (c == '}') {
			if (s.empty() || s.top() != '{') {
					return false;
			}
			s.pop();
		}
		i++;
	}
	return s.empty();
}

