#include "./location.class.hpp"

Location::Location() {
	// fill with default values
	this->autoindex = "";
	this->index = "";
	this->root = "";
	this->upload_enable = "off";
	this->upload_path = "";
}

// getters
std::string Location::getAutoindex() const {
	return this->autoindex;
}
std::string Location::getIndex() const {
	return this->index;
}
std::vector<std::string> Location::getAllowMethods() const {
	return this->allow_methods;
}
std::string Location::getRoot() const {
	return this->root;
}
std::string Location::getUploadEnable() const {
	return this->upload_enable;
}
std::string Location::getUploadStore() const {
	return this->upload_path;
}
std::string Location::getLocationPath() const {
	return this->locationPath;
}

// setters
void Location::setAutoindex(std::string autoindex) {
	this->autoindex = autoindex;
}
void Location::setIndex(std::string index) {
	this->index = index;
}
void Location::setAllowedMethods(std::vector<std::string> allow_methods) {
	this->allow_methods = allow_methods;
}
void Location::setRoot(std::string root) {
	this->root = root;
}
void Location::setUploadEnable(std::string upload_enable) {
	this->upload_enable = upload_enable;
}
void Location::setUploadPath(std::string upload_path) {
	this->upload_path = upload_path;
}
void Location::setLocationPath(std::string locationPath) {
	this->locationPath = locationPath;
}

// other methods
void Location::printLocation() const {
	std::cout << "autoindex: " << this->autoindex << std::endl;
	std::cout << "index: " << this->index << std::endl;
	std::cout << "allow_methods: ";
	for (size_t i = 0; i < this->allow_methods.size(); i++) {
		std::cout << this->allow_methods[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "root: " << this->root << std::endl;
	std::cout << "upload_enable: " << this->upload_enable << std::endl;
	std::cout << "upload_path: " << this->upload_path << std::endl;
}

void Location::clearLocation() {
	this->autoindex = "";
	this->index = "";
	this->allow_methods.clear();
	this->root = "";
	this->upload_enable = "";
	this->upload_path = "";
}

// destructor
Location::~Location() {
	this->clearLocation();
}
