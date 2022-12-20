#pragma once

#include <iostream>
#include <vector>
#include "../config-data/config.class.hpp"
#include <stack>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include "./parse.config.hpp"
#include "../utils/utils.hpp"

void loadingConfig();
std::vector<Config> descentParser(const std::string path);
const std::vector<std::string> grapServers(std::string &content);
std::string getServer(std::string &content);
const Config parseServer(std::string &content);
std::string getLine(std::string &content);
std::vector<int> getPorts(std::string line);
bool isPortNumber(std::string port);
void analyzeLine(std::string &line);
void analyzeServerContent(std::string &content);
void parseServerContent(std::string &line, Config &server);
void parseLocationContent(std::string &content, Config &server);
std::vector<std::string> getServerNames(std::string serverNames);
void analyzeServerNames(std::vector<std::string> serverNames);
bool analyzeRepeatedElements(std::vector<std::string> elements);
std::string getHostname(std::string line);
int getClientMaxBodySize(std::string line);
std::string getServerRoot(std::string line);
void analyzeLocationContent(std::string locations, Config &server);
std::string getLocationPath(std::string path);
bool isValidUrlPath(const std::string& path);
bool isValidFilePath(const std::string& path);
std::string getAutoindex(std::string autoindex);
std::string getIndex(std::string filePath);
std::string getLocationRoot(std::string root);
std::string getUploadEnable(std::string str);
std::string getUploadPath(std::string str);
std::vector<std::string> getAllowedMethods(std::string str);
bool hasValidBraces(const std::string& str);
std::vector<std::string> getRedirect(std::string line);