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

#ifdef _WIN32
#include <windows.h>
#endif

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


bool Config::ExtractMap(const std::string& filename) {
    std::unordered_map<std::string, std::string> map;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << "\n";
        return false;
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
    return true;
}

void Config::showConfig(std::vector<std::string> &logs) const {
    logs.clear();
    logs.push_back("Current configuration:");
    if (_irToAction.empty()) {
        logs.push_back("No config loaded.");
        return;
    }
    for (const auto& [key, value] : _irToAction) {
        logs.push_back("  " + key + " -> " + value);
    }
}

void Config::addMapping(const std::string& irCode, const std::string& action) {
    _irToAction[irCode] = action;
    // std::cout << "Added mapping: " << irCode << " -> " << action << "\n";
}

#ifdef _WIN32
void Config::pressKey(const std::vector<std::string>& keys) {
    
    std::vector<INPUT> inputs;

    std::unordered_map<std::string, WORD> keyMap = {
        {"ctrl", VK_CONTROL}, {"alt", VK_MENU}, {"shift", VK_SHIFT},
        {"space", VK_SPACE}, {"enter", VK_RETURN}, {"esc", VK_ESCAPE},
        {"f", 0x46}, {"t", 0x54}, {"w", 0x57},
        {"volumemute", VK_VOLUME_MUTE}, {"volumeup", VK_VOLUME_UP}, {"volumedown", VK_VOLUME_DOWN},
        // Ajoute les autres touches ici si nécessaire
    };

    // 1. Appui de toutes les touches (modificateurs d'abord)
    for (const auto& key : keys) {
        if (keyMap.find(key) != keyMap.end()) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = keyMap[key];
            inputs.push_back(input);
        }
    }

    // 2. Relâchement dans l'ordre inverse
    for (auto it = keys.rbegin(); it != keys.rend(); ++it) {
        if (keyMap.find(*it) != keyMap.end()) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = keyMap[*it];
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            inputs.push_back(input);
        }
    }

    SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
}

void Config::openSite(const std::string& url) {
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
#endif

Config::~Config()
{
}
