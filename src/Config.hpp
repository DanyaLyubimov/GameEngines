#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Config{
public:
    void load(const std::string& path);
    void printConfigs() const;

    int getInt(const std::string& key, int i) const;
    std::vector<int> getIntVec(const std::string& key) const;
    float getFloat(const std::string& key, int i) const;
    std::string getString(const std::string& key, int i) const;
private:
    std::unordered_map<std::string, std::vector<float>> floatValues;
    std::unordered_map<std::string, std::vector<int>> intValues;
    std::unordered_map<std::string, std::vector<std::string>> stringValues;
};
