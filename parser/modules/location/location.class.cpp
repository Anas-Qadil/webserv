#include "./location.class.hpp"

Location::Location() {
	// fill with default values
	this->autoindex = "";
	this->index = "";
	this->root = "";
	this->upload_enable = "";
	this->upload_path = "";
	this->return_path = "";
	this->return_code = -1;
	this->fastcgi_pass = "";
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
std::string Location::getFastcgiPass() const {
	return this->fastcgi_pass;
}
std::string Location::get_CGI_BIN() const {
	return this->cgi_bin;
}

// setters
void Location::setAutoindex(std::string autoindex) {
	// check if autoindex already exists
	if (this->autoindex != "")
		throw std::runtime_error("Error: You can't set autoindex twice");
	this->autoindex = autoindex;
}
void Location::setIndex(std::string index) {
	// check if index already exists
	if (this->index != "")
		throw std::runtime_error("Error: You can't set location's index twice");
	this->index = index;
}
void Location::setAllowedMethods(std::vector<std::string> allow_methods) {
	// check if allow_methods already exists
	if (this->allow_methods.size() != 0)
		throw std::runtime_error("Error: You can't set location's allowed methods twice");
	this->allow_methods = allow_methods;
}
void Location::setRoot(std::string root) {
	// check if root already exists
	if (this->root != "")
		throw std::runtime_error("Error: You can't set location root twice");
	this->root = root;
}
void Location::setUploadEnable(std::string upload_enable) {
	// check if upload_enable already exists
	if (this->upload_enable != "")
		throw std::runtime_error("Error: You can't set uploadEnabled twice");
	this->upload_enable = upload_enable;
}
void Location::setUploadPath(std::string upload_path) {
	// check if upload_path already exists
	if (this->upload_path != "")
		throw std::runtime_error("Error: You can't set upload path twice");
	this->upload_path = upload_path;
}
void Location::setLocationPath(std::string locationPath) {
	// check if locationPath already exists
	if (this->locationPath != "")
		throw std::runtime_error("Error: You can't set location path twice");
	this->locationPath = locationPath;
}
void Location::setReturnPath(std::string return_path) {
	// check if return_path already exists
	if (this->return_path != "")
		throw std::runtime_error("Error: You can't set return path twice");
	this->return_path = return_path;
}
void Location::setReturnCode(int return_code) {
	this->return_code = return_code;
}
void Location::setFastcgiPass(std::string fastcgi_pass) {
	// check if fastcgi_pass already exists
	if (this->fastcgi_pass != "")
		throw std::runtime_error("Error: You can't set fast cgi pass twice");
	this->fastcgi_pass = fastcgi_pass;
}
void Location::setCgiBin(std::string cgi_bin) {
	// check if cgi_bin already exists
	if (this->cgi_bin != "")
		throw std::runtime_error("Error: You can't set cgi bin twice");
	this->cgi_bin = cgi_bin;
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
	if (this->return_code != -1)
		std::cout << "return_code: " << this->return_code << std::endl;
	if (this->cgi_bin != "")
		std::cout << "cgi_bin: " << this->cgi_bin << std::endl;
	if (this->fastcgi_pass != "")
		std::cout << "fastcgi_pass: " << this->fastcgi_pass << std::endl;
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
