#pragma once

#include <iostream>
#include <vector>
#include "../config-data/config.class.hpp"

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
void parseLocationContent(std::string &content, Config &location);
std::vector<std::string> getServerNames(std::string serverNames);
void analyzeServerNames(std::vector<std::string> serverNames);
bool analyzeRepeatedElements(std::vector<std::string> elements);