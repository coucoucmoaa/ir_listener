/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Config
*/

#include "Config.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <map>
#include <algorithm>

Config::Config(const std::string& name)
    : _name(name) {}

void Config::listenAndMap(const std::string &irCode) {
    std::string action;

    if (_irToAction.find(irCode) == _irToAction.end()) {
        std::cout << "New IR code: " << irCode << "\n";
        std::cout << "Enter action name for this IR code: ";
        std::getline(std::cin, action);
        _irToAction[irCode] = action;
    } else {
        std::cout << "IR code already mapped.\n";
    }
}

void Config::saveToJson(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << "\n";
        return;
    }

    file << "{\n";
    bool first = true;
    for (const auto& [code, action] : _irToAction) {
        if (!first)
            file << ",\n";
        file << "  \"" << code << "\": \"" << action << "\"";
        first = false;
    }
    file << "\n}\n";

    std::cout << "Configuration saved to " << filename << "\n";
}

const std::unordered_map<std::string, std::string>& Config::getMap() const {
    return _irToAction;
}


void Config::ExtractMap(const std::string& filename) {
    std::unordered_map<std::string, std::string> map;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        // Skip empty lines or lines that don't contain ':'
        if (line.empty() || line.front() == '{' || line.front() == '}' || line.find(':') == std::string::npos)
            continue;

        size_t keyStart = line.find('\"');
        size_t keyEnd = line.find('\"', keyStart + 1);
        size_t valStart = line.find('\"', keyEnd + 1);
        size_t valEnd = line.find('\"', valStart + 1);

        if (keyStart == std::string::npos || keyEnd == std::string::npos ||
            valStart == std::string::npos || valEnd == std::string::npos)
            continue;

        std::string key = line.substr(keyStart + 1, keyEnd - keyStart - 1);
        std::string value = line.substr(valStart + 1, valEnd - valStart - 1);

        map[key] = value;
    }

    _irToAction = map;
}

void Config::showConfig() {
    std::cout << "Current configuration:\n";
    if (_irToAction.empty()) {
        std::cout << "No config loaded.\n";
        return;
    }
    for (const auto& [key, value] : _irToAction) {
        std::cout << "  " << key << " -> " << value << "\n";
    }
}

Config::~Config()
{
}
