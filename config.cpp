#include "config.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


std::unordered_map<std::string, std::vector<float>> configFloat;
std::unordered_map<std::string, std::vector<int>> configInt;
std::unordered_map<std::string, std::vector<std::string>> configString;

void loadConfig(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    while (std::getline(file,line))
    {   
        std::cout<<line<<"\n";
        std::istringstream iss(line);

        std::string type, key;
        iss >> type >> key;

        if (type == "int"){
            int v;
            std::vector<int> values;
            while (iss >> v)
                values.push_back(v);

            configInt[key] = values;
        }
        else if (type == "float"){
            float v;
            std::vector<float> values;
            while (iss >> v)
                values.push_back(v);

            configFloat[key] = values;
        }
        else if (type == "string"){
            std::string v;
            std::vector<std::string> values;
            while (iss >> v)
                values.push_back(v);

            configString[key] = values;
        }
        
    }
}

void printConfigs()
{
    for (const auto& [key, values] : configInt)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n=== FLOAT CONFIG ===\n";
    for (const auto& [key, values] : configFloat)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n=== STRING CONFIG ===\n";
    for (const auto& [key, values] : configString)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }
}