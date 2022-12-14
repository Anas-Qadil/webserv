#pragma once

#include <iostream>
#include <vector>
#include "../config-data/config.class.hpp"

void loadingConfig();
std::vector<Config> descentParser(const std::string path);
const std::vector<std::string> grapServers(std::string &content);
std::string getServer(std::string &content);