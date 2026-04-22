#include "Config.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


void Config::load(const std::string& path)
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

            intValues[key] = values;
        }
        else if (type == "float"){
            float v;
            std::vector<float> values;
            while (iss >> v)
                values.push_back(v);

            floatValues[key] = values;
        }
        else if (type == "string"){
            std::string v;
            std::vector<std::string> values;
            while (iss >> v)
                values.push_back(v);

            stringValues[key] = values;
        }
        
    }
}

void Config::printConfigs() const
{
    std::cout << "\n=== INT CONFIG ===\n";
    for (const auto& [key, values] : intValues)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n=== FLOAT CONFIG ===\n";
    for (const auto& [key, values] : floatValues)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n=== STRING CONFIG ===\n";
    for (const auto& [key, values] : stringValues)
    {
        std::cout << key << ": ";
        for (const auto& v : values)
            std::cout << v << " ";
        std::cout << "\n";
    }
}

int Config::getInt(const std::string& key, int i) const
{
    return intValues.at(key)[i];
}

 std::vector<int> Config::getIntVec(const std::string& key) const
{
    return intValues.at(key);
}


float Config::getFloat(const std::string& key, int i) const
{
    return floatValues.at(key)[i];
}

std::string Config::getString(const std::string& key, int i) const
{
    return stringValues.at(key)[i];
}