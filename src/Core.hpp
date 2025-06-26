/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

// #include "Linux.hpp"
#include "Profil.hpp"
#include "ISerialBackend.hpp"
#include "Config.hpp"
#include <functional>

class Core {
    public:
        Core(std::string os);
        ~Core();
        void loop();
        void createConfig(ISerialBackend* serial, const std::string& configName);
        void loadConfig(const std::string& configName);
        void startListening(ISerialBackend* serial);
        void displayActions();
        void debug(ISerialBackend* serial);

        // void saveConfig();
        // void removeConfig();
        // void listConfigs();
        // void readConfig();
        // void writeConfig();
        // void stopListening();


    protected:
        int _serialPort = -1;;
        // Linux _linuxConfig;
        ISerialBackend* _backend;
        Config _config;
        std::unordered_map<std::string, std::function<void()>> _actions;
        bool _stopListening = false;
        std::string cleanBuffer(const std::string& buffer);
        // Windows _windowsConfig;
        // std::vector<std::string> _configs;
        // std::string _currentConfig;
        // std::string _configFilePath;
        // std::string _configName;
        // Profil _profil;
    private:
};

#endif /* !CORE_HPP_ */
