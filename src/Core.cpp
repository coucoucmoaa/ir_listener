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

Core::Core(std::string os) : _config("default_config"), _stopListening(false)
{
    // Implémentation du constructeur
    // Par exemple :
    (void)os; // si tu n'utilises pas encore os, pour éviter warning
    // ... initialisations
   _actions = {
    {"0", []() { std::cout << "Action NONE selected." << std::endl; }},
    {"2", []() { system("xdotool click 1"); }},  // Clic gauche
    {"3", []() { system("xdotool click 3"); }},  // Clic droit
    {"4", []() { system("xdotool key ctrl+w"); }},  // Fermer onglet
    {"5", []() { system("xdotool key ctrl+t"); }},  // Nouvel onglet
    {"6", []() { system("xdg-open https://www.youtube.com &"); }},
    {"7", []() { system("xdg-open https://www.twitch.tv &"); }},
    {"8", []() { system("xdg-open https://www.netflix.com &"); }},
    {"9", []() { system("xdg-open https://discord.com/app &"); }},
    {"10", []() { system("xdg-open https://zoro.to &"); }},  // Exemple site anime
    {"11", []() { system("amixer set Master 5%+"); }},
    {"12", []() { system("amixer set Master 5%-"); }},
    {"13", []() { system("amixer set Master toggle"); }},  // Mute / Unmute
    {"14", []() { system("xdotool key space"); }},  // Pause / Play
    {"15", []() { system("xdotool key f"); }},      // Plein écran
    {"16", []() { system("xdotool key ctrl+Tab"); }}  // Changer d'onglet
};
    _actions["1"] = [&]() {
        std::cout << "Stopping listener..." << std::endl;
        _stopListening = true;
    };
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
        } else if (command == "debug"){
            debug(serial);
        } else if (command == "action"){
            displayActions(); // Implémentation de la fonction d'affichage des actions
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

void Core::displayActions() {
    std::cout << "Available actions:\n";
    std::cout << "0. NONE\n";
    std::cout << "1. STOP\n";
    std::cout << "2. MOUSELEFTC\n";
    std::cout << "3. MOUSERIGHTC\n";
    std::cout << "4. CTRLW\n";
    std::cout << "5. CTRLT\n";
    std::cout << "6. YOUTUBE\n";
    std::cout << "7. TWITCH\n";
    std::cout << "8. NETFLIX\n";
    std::cout << "9. DISCORD\n";
    std::cout << "10. ANIME\n";
    std::cout << "11. VOLUMEUP\n";
    std::cout << "12. VOLUMEDOWN\n";
    std::cout << "13. VOLUMEMUTE\n";
    std::cout << "14. PAUSE\n";
    std::cout << "15. FULLSCREEN\n";
    std::cout << "16. TOGGLE\n";
    std::cout << "Please select an action by number." << std::endl;     
}

std::string Core::cleanBuffer(const std::string& buffer) {
    std::string result;
    for (char c : buffer) {
        if (isprint(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    return result;
}

void Core::startListening(ISerialBackend* serial) {
    // Implémentation de la fonction de démarrage de l'écoute
    std::cout << "Starting to listen for IR codes..." << std::endl;
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
                        auto it = _config.getMap().find(buffer);
                        if (it != _config.getMap().end()) {
                            auto action = _actions.find(it->second);
                            if (action != _actions.end()) {
                                action->second();
                                std::cout << "Action executed for IR code: " << buffer << std::endl;
                            }
                        }
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }
}

void Core::debug(ISerialBackend* serial) {
    char ch;
    std::string buffer;

    while (true)
    {
        if (serial->readChar(ch) > 0) {
            if (ch == '\n' || ch == '\r') {
                if (!buffer.empty()) {
                    if (buffer != "0x0") {
                        std::cout << "Debug: Received IR code: " << buffer << std::endl;
                    } else {
                        std::cout << "Debug: Received empty IR code." << std::endl;
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
