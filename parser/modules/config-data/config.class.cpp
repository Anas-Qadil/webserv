/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:18:32 by aqadil            #+#    #+#             */
/*   Updated: 2023/01/08 10:22:08 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream>
#include "./config.class.hpp"
#include <set>

Config::Config() {
	// fill with default values
	this->host = "";
	this->client_max_body_size = 0;
	this->root = "";
}
// copy constructor
Config::Config(const Config &config) {
	this->location = config.location;
	this->port = config.port;
	this->server_name = config.server_name;
	this->host = config.host;
	this->client_max_body_size = config.client_max_body_size;
	this->root = config.root;
	this->error_page = config.error_page;
	this->allow_methods = config.allow_methods;
}

// getters
std::map<std::string, Location> Config::getLocation() const {
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
size_t Config::getClientMaxBodySize() const {
	return this->client_max_body_size;
}
std::string Config::getRoot() const {
	return this->root;
}
std::map<std::string, std::string> Config::getErrorPage() const {
	// std::cout << "error page size: " << this->error_page.size() << std::endl;
	return this->error_page;
}
std::vector<std::string> Config::get_Methods() const {
	return this->allow_methods;
}

// setters
void Config::setLocation(std::string locationPath, Location location) {
	if (this->location.find(locationPath) != this->location.end())
		throw std::runtime_error("error: location already exists");
	this->location[locationPath] = location;
}
void Config::setPort(std::vector<int> port) {
	// check if port already exists
	if (this->port.size() > 0)
		throw std::runtime_error("error: You can only set port once");
	this->port = port;
}
void Config::setServerName(std::vector<std::string> server_name) {
	// check if server_name already exists
	if (this->server_name.size() > 0)
		throw std::runtime_error("error: You can only set server_name once");
	this->server_name = server_name;
}
void Config::setHost(std::string host) {
	this->host = host;
}
void Config::setClientMaxBodySize(size_t client_max_body_size) {
	// check if client_max_body_size already exists
	if (this->client_max_body_size > 0)
		throw std::runtime_error("error: You can only set client_max_body_size once");
	this->client_max_body_size = client_max_body_size;
}
void Config::setRoot(std::string root) {
	// check if root already exists
	if (this->root != "")
		throw std::runtime_error("error: You can only set root once");
	this->root = root;
}
void Config::setErrorPage(std::map<std::string, std::string> error_page) {
	// check if error_page already exists
	if (this->error_page.size() > 0)
		throw std::runtime_error("error: You can only set error_page once");
	// check if map has duplicate keys
	this->error_page = error_page;
}
void Config::setAllowedMethods(std::vector<std::string> allow_methods) {
	// check if allow_methods already exists
	if (this->allow_methods.size() > 0)
		throw std::runtime_error("error: You can only set allow_methods once");
	this->allow_methods = allow_methods;
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
	// allow_methods
	if (!this->allow_methods.empty()) {
		std::cout << "allow_methods: ";
		for (std::vector<std::string>::const_iterator it = this->allow_methods.begin(); it != this->allow_methods.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "host: " << this->host << std::endl;
	std::cout << "client_max_body_size: " << this->client_max_body_size << std::endl;
	std::cout << "root: " << this->root << std::endl;
	// check if error_page is empty
	// if (!this->error_page.empty()) {
	// loop through error_page map
		std::cout << "error_page: ";
		for (std::map<std::string, std::string>::const_iterator it = this->error_page.begin(); it != this->error_page.end(); ++it) {
			std::cout << it->first << " " << it->second << " ";
		}
		std::cout << std::endl;
	// }
	std::cout << "---------------------- Location -------------------------" << std::endl;
	// loop through location map
	for (std::map<std::string, Location>::const_iterator it = this->location.begin(); it != this->location.end(); ++it) {
		std::cout << "location: " << it->first << std::endl;
		it->second.printLocation();
		std::cout << "---------------------------------------------------------" << std::endl;
	}
}

void Config::clear() {
	this->location.clear();
	this->port.clear();
	this->server_name.clear();
	this->host.clear();
	this->client_max_body_size = 0;
	this->root.clear();
	this->error_page.clear();
}

Config::~Config() {
	this->location.clear();
	this->port.clear();
	this->server_name.clear();
	this->host.clear();
	this->client_max_body_size = 0;
	this->root.clear();
	this->error_page.clear();
}
