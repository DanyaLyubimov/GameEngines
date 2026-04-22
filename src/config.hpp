#pragma once

#include <string>
#include <unordered_map>
#include <vector>

extern std::unordered_map<std::string, std::vector<float>> configFloat;
extern std::unordered_map<std::string, std::vector<int>> configInt;
extern std::unordered_map<std::string, std::vector<std::string>> configString;

void loadConfig(const std::string& path);
void printConfigs();