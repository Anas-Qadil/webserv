#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

const std::string readFile(std::string path);
void analyze(std::string &content);
void formatLine(std::string &line);
bool checkBrackets(std::string str);
void generaleCheck(std::string countent);
void generaleFormat(std::string &content);