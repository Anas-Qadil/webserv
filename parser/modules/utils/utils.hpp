#pragma once

#include <iostream>
#include <vector>
#include <fstream>

const std::string readFile(std::string path);
void analyze(std::string &content);
void formatLine(std::string &line);
int checkBrackets(std::string content);
void generaleCheck(std::string countent);
void generaleFormat(std::string &content);