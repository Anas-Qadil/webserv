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
std::string Location::getReturnPath() const {
	return this->return_path;
}
int Location::getReturnCode() const {
	return this->return_code;
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
void Location::setReturnPath(std::string return_path) {
	this->return_path = return_path;
}
void Location::setReturnCode(int return_code) {
	this->return_code = return_code;
}

// other methods
void Location::printLocation() const {
	if (this->autoindex != "")
		std::cout << "autoindex: " << this->autoindex << std::endl;
	if (this->index != "")
		std::cout << "index: " << this->index << std::endl;
	if (this->allow_methods.size() > 0)
	{
		std::cout << "allow_methods: ";
		for (size_t i = 0; i < this->allow_methods.size(); i++) {
			std::cout << this->allow_methods[i] << " ";
		}
		std::cout << std::endl;
	}
	if (this->root != "")
		std::cout << "root: " << this->root << std::endl;
	if (this->upload_enable != "")
		std::cout << "upload_enable: " << this->upload_enable << std::endl;
	if (this->upload_path != "")
		std::cout << "upload_path: " << this->upload_path << std::endl;
	if (this->return_path != "")
		std::cout << "return_path: " << this->return_path << std::endl;
	if (this->return_code != 0)
		std::cout << "return_code: " << this->return_code << std::endl;
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
