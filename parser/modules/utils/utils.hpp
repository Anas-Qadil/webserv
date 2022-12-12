#pragma once

#include <iostream>
#include <vector>
#include <fstream>

const std::string readFile(std::string path);
const std::vector<std::string> grapServers(std::string content);
void analyze(std::string &content);
void formatLine(std::string &line);
int checkBrackets(std::string content);