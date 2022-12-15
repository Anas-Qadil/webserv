#include <iostream>
#include "./config.class.hpp"

Config::Config() {
	// fill with default values
	this->location = Location();
	this->port.push_back(80);
	this->server_name.push_back("localhost");
	this->host = "localhost";
	this->client_max_body_size = 1;
	this->root = "/";
}
// copy constructor
Config::Config(const Config &config) {
	this->location = config.location;
	this->port = config.port;
	this->server_name = config.server_name;
	this->host = config.host;
	this->client_max_body_size = config.client_max_body_size;
	this->root = config.root;
}

// getters
Location Config::getLocation() const {
	return this->location;
}
std::vector<int> Config::getPort() const {
	return this->port;
}
std::vector<std::string> Config::getServerName() const {
	return this->server_name;
}
std::string Config::getHost() const {
	return this->host;
}
int Config::getClientMaxBodySize() const {
	return this->client_max_body_size;
}
std::string Config::getRoot() const {
	return this->root;
}

// setters
void Config::setLocation(Location location) {
	this->location = location;
}
void Config::setPort(std::vector<int> port) {
	this->port = port;
}
void Config::setServerName(std::vector<std::string> server_name) {
	this->server_name = server_name;
}
void Config::setHost(std::string host) {
	this->host = host;
}
void Config::setClientMaxBodySize(int client_max_body_size) {
	this->client_max_body_size = client_max_body_size;
}
void Config::setRoot(std::string root) {
	this->root = root;
}

// other methods
void Config::print() const {
	std::cout << "--------------------- Server Config ---------------------" << std::endl;
	// when location is implemented, uncomment this
	// loop through port vector
	std::cout << "port: ";
	for (std::vector<int>::const_iterator it = this->port.begin(); it != this->port.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	// loop through server_name vector
	std::cout << "server_name: ";
	for (std::vector<std::string>::const_iterator it = this->server_name.begin(); it != this->server_name.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "host: " << this->host << std::endl;
	std::cout << "client_max_body_size: " << this->client_max_body_size << std::endl;
	std::cout << "root: " << this->root << std::endl;
	std::cout << "---------------------- Location -------------------------" << std::endl;
	this->location.printLocation();
	std::cout << "---------------------------------------------------------" << std::endl;
}

void Config::clear() {
	this->location = Location();
	this->port.clear();
	this->server_name.clear();
	this->host.clear();
	this->client_max_body_size = 0;
	this->root.clear();
}

Config::~Config() {
	// std::cout << "Config destructor called" << std::endl;
}
