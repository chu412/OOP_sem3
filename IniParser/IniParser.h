#pragma once
#include <string>
#include <vector>
#include <map>

class IniParser {
public:

    IniParser() = default;
    explicit IniParser(const std::string& file); 
    ~IniParser() = default;
    void load(const std::string& file); 
    bool hasSection(const std::string& name) const;
    bool hasParam(const std::string& section, const std::string& param) const;
    template<class T> T get(const std::string& section, const std::string& param) const; 
    void print() const;

private:
    void parse();
    std::vector<std::string> input;
    std::map<std::string, std::map<std::string, std::string>> data;

};
