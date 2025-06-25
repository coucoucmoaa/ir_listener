/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#include "Core.hpp"
#include "SerialFactory.hpp"

#include "LinuxSerialBackend.hpp"
#include "WindowsSerialBackend.hpp"
// #include <unistd.h>
// #include <sys/wait.h>
// #include <chrono>/

Core::Core(std::string os) : _config("default_config"){
    // Implémentation du constructeur
    // Par exemple :
    (void)os; // si tu n'utilises pas encore os, pour éviter warning
    // ... initialisations
}

void Core::loop() {
    ISerialBackend* serial = createSerialBackend();

#ifdef _WIN32
    const std::string portName = "COM3";
#else
    const std::string portName = "/dev/ttyUSB0";
#endif

    if (!serial || !serial->openPort(portName)) {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        delete serial;
        return;
    }

    std::string buffer;
    char ch;
    std::string command;

    while (true) {
        std::getline(std::cin, command);
        if (command == "exit") {
            std::cout << "Exiting loop." << std::endl;
            break;
        }
        // if (command == "help") {
        // }
        if (command.rfind("nc ", 0) == 0 && command.size() > 3) {
            createConfig(serial, command.substr(3)); // tout après "nc "
        } else if (command == "sc") {
            _config.showConfig(); // Implémentation de la fonction d'affichage de configuration
        } else if (command.rfind("lc ", 0) == 0 && command.size() > 3) {
            loadConfig(command.substr(3)); // Implémentation de la fonction de chargement de configuration
        } else if (command == "start"){
            if (_config.getMap().empty()) {
                std::cout << "No configuration loaded. Please load a configuration first." << std::endl;
                continue;
            }
            this->startListening(serial);
        } else {
            std::cout << "Usage: <command> <config_name> (config name not mandatory for ls and sc)" << std::endl;
        }
        // N = Name
        // nc N  .. new config
        // lc N  .. load config
        // sc N  .. save config
        // rc N  .. remove config
        // ls    .. list configs
        // sc    .. show current config
        // exit
    }
    serial->closePort();
    delete serial;
}

void Core::createConfig(ISerialBackend* serial, const std::string& configName) {
    // Implémentation de la création de configuration
    std::cout << "Creating configuration..." << std::endl;
    std::cout << "press any button on your remote to map it to an action." << std::endl;
    std::string buffer;
    char ch;
    std::string answer;

    while (true) {
        if (serial->readChar(ch) > 0) {
            if (ch == '\n' || ch == '\r') {
                if (!buffer.empty()) {
                    if (buffer == "IR Receiver Ready") {
                        buffer.clear();
                        continue;
                    }
                    if (buffer != "0x0") {
                        _config.listenAndMap(buffer);
                        std::cout << "Do you want to map another button? (y/n): "<< std::flush;
                        std::getline(std::cin, answer);
                        if (answer == "n") {
                            break;
                        }
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }
    _config.saveToJson("configs/" + configName + ".json");
    std::cout << configName << ".json" << " loaded by default." << std::endl;
}

void Core::loadConfig(const std::string& configName) {
    // Implémentation de la fonction de chargement de configuration
    std::cout << "Loading configuration: " << configName << std::endl;
    // _config.setMap(_config.getMap()); // Simule le chargement de la configuration
    // std::cout << "Configuration loaded." << std::endl;
    _config.ExtractMap("configs/" + configName + ".json");
    std::cout << "Configuration " << configName << " loaded." << std::endl;
    for (const auto& [key, value] : _config.getMap()) {
        std::cout << "IR Code: " << key << " -> Action: " << value << std::endl;
    }
}

void Core::startListening(ISerialBackend* serial) {
    // Implémentation de la fonction de démarrage de l'écoute
    std::cout << "Starting listening..." << std::endl;
    char ch;
    std::string buffer;

    while (true) {
        if (serial->readChar(ch) > 0) {
            if (ch == '\n' || ch == '\r') {
                if (!buffer.empty()) {
                    if (buffer == "IR Receiver Ready") {
                        buffer.clear();
                        continue;
                    }
                    if (buffer != "0x0") {
                        
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }
}

Core::~Core()
{
}
