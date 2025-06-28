/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#include "Core.hpp"
#include "RaylibSafe.hpp"
#include "SerialFactory.hpp"
#include "LinuxSerialBackend.hpp"
#include "WindowsSerialBackend.hpp"

Core::Core(std::string os) : _config("default_config"), _stopListening(false)
{
    (void)os;
    #ifdef _WIN32
    _actions = {
        {"0", [this]() { std::cout << "Action NONE selected." << std::endl; }},
        {"2", [this]() { _config.leftClick(); }},
        {"3", [this]() { _config.rightClick(); }},
        {"4", [this]() { _config.pressKey({"ctrl", "w"}); }},
        {"5", [this]() { _config.pressKey({"ctrl", "t"}); }},
        {"6", [this]() { _config.openSite("https://youtube.com"); }},
        {"7", [this]() { _config.openSite("https://twitch.tv"); }},
        {"8", [this]() { _config.openSite("https://netflix.com"); }},
        {"9", [this]() { _config.openSite("https://discord.com"); }},
        {"10", [this]() { _config.openSite("https://myanimelist.net"); }},
        {"11", [this]() { _config.pressKey({"volumeup"}); }},
        {"12", [this]() { _config.pressKey({"volumedown"}); }},
        {"13", [this]() { _config.pressKey({"volumemute"}); }},
        {"14", [this]() { _config.pressKey({"space"}); }},
        {"15", [this]() { _config.pressKey({"f"}); }},
        {"16", [this]() { _config.pressKey({"ctrl", "t"}); }},
        {"17", [this]() { _config.moveMouse(0, -100); }},  // Up
        {"18", [this]() { _config.moveMouse(0, 100); }},   // Down
        {"19", [this]() { _config.moveMouse(-100, 0); }},  // Left
        {"20", [this]() { _config.moveMouse(100, 0); }}    // Right
    };
    #endif

    #ifdef __linux__
    _actions = {
        {"0", []() { std::cout << "Action NONE selected." << std::endl; }},
        {"2", []() { system("xdotool click 1"); }},
        {"3", []() { system("xdotool click 3"); }},
        {"4", []() { system("xdotool key ctrl+w"); }},  // Close tab
        {"5", []() { system("xdotool key ctrl+t"); }},  // New tab
        {"6", []() { system("xdg-open https://www.youtube.com &"); }},
        {"7", []() { system("xdg-open https://www.twitch.tv &"); }},
        {"8", []() { system("xdg-open https://www.netflix.com &"); }},
        {"9", []() { system("xdg-open https://discord.com/app &"); }},
        {"10", []() { system("xdg-open https://zoro.to &"); }},
        {"11", []() { system("amixer set Master 5%+"); }},
        {"12", []() { system("amixer set Master 5%-"); }},
        {"13", []() { system("amixer set Master toggle"); }},  // Mute / Unmute
        {"14", []() { system("xdotool key space"); }},  // Pause / Play
        {"15", []() { system("xdotool key f"); }},      // Fullscreen
        {"16", []() { system("xdotool key ctrl+Tab"); }},  // Tab switch
        {"17", []() { system("xdotool mousemove_relative 0 -100"); }},
        {"18", []() { system("xdotool mousemove_relative 0 100"); }},
        {"19", []() { system("xdotool mousemove_relative -100 0"); }},
        {"20", []() { system("xdotool mousemove_relative 100 0");}} 
    };
    #endif


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
    _serial = serial;
}

void Core::loop() {



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
            createConfig(_serial, command.substr(3)); // tout après "nc "
        } else if (command == "debug"){
            debug(_serial);
        } else if (command == "action"){
            displayActions(); // Implémentation de la fonction d'affichage des actions
        } else if (command == "sc") {
            // _config.showConfig(); // Implémentation de la fonction d'affichage de configuration
        } else if (command.rfind("lc ", 0) == 0 && command.size() > 3) {
            loadConfig(command.substr(3)); // Implémentation de la fonction de chargement de configuration
        } else if (command == "start"){
            if (_config.getMap().empty()) {
                std::cout << "No configuration loaded. Please load a configuration first." << std::endl;
                continue;
            }
            this->startListening(_serial);
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
    _serial->closePort();
    delete _serial;
}

std::function<void()> promptHandler = nullptr;

void Core::createConfig(ISerialBackend* serial, const std::string& configName)
{
    this->configName = configName;
    this->logs.clear();
    this->currentIRcode.clear();
    this->inputActionName.clear();
    this->isMapping = true;
    this->_serial = serial;

    this->logs.push_back("Creating configuration: " + configName);
    this->logs.push_back("Press a button on your remote to map it...");

    enum MappingStep {
        WAIT_IR_CODE,
        ASK_ACTION_NAME,
        WAIT_ACTION_NAME_INPUT,
        ASK_CONTINUE
    };

    static MappingStep step = WAIT_IR_CODE;
    static std::string savedIRcode; // Variable pour sauvegarder le code IR

    this->deferredAction = [this]() mutable {
        char ch;
        switch (step) {
            case WAIT_IR_CODE:
                if (this->_serial->readChar(ch) > 0) {
                    if (ch == '\n' || ch == '\r') {
                        if (!this->currentIRcode.empty()) {
                            if (this->currentIRcode == "IR Receiver Ready") {
                                this->currentIRcode.clear();
                                return;
                            }
                            if (this->currentIRcode != "0x0") {
                                // Debug: Afficher le code IR reçu
                                std::cout << "DEBUG: IR Code reçu: '" << this->currentIRcode << "'\n";
                                
                                savedIRcode = this->currentIRcode; // SAUVEGARDER le code IR ici !
                                
                                this->logs.push_back("IR Code detected: " + this->currentIRcode);
                                this->logs.push_back("Enter action name for: " + this->currentIRcode);
                                this->isWaitingForInput = true;
                                step = WAIT_ACTION_NAME_INPUT;
                            }
                            this->currentIRcode.clear(); // On peut maintenant effacer
                        }
                    } else if (isprint(ch)) {
                        this->currentIRcode += ch;
                    }
                }
                break;

            case WAIT_ACTION_NAME_INPUT:
                if (!this->inputActionName.empty()) {
                    // Debug: Afficher ce qu'on va mapper
                    std::cout << "DEBUG: Mapping '" << savedIRcode << "' -> '" << this->inputActionName << "'\n";
                    
                    this->_config.addMapping(savedIRcode, this->inputActionName); // Utiliser le code sauvegardé !
                    this->logs.push_back("Mapped: " + savedIRcode + " => " + this->inputActionName);
                    this->logs.push_back("Map another button? Press Y or N...");
                    
                    savedIRcode.clear(); // Nettoyer la sauvegarde
                    this->inputActionName.clear();
                    this->isWaitingForInput = false;
                    step = ASK_CONTINUE;
                }
                break;

            case ASK_CONTINUE:
                if (IsKeyPressed(KEY_Y)) {
                    this->logs.push_back("Waiting for next IR input...");
                    step = WAIT_IR_CODE;
                }
                if (IsKeyPressed(KEY_N)) {
                    this->_config.saveToJson("configs/" + this->configName + ".json");
                    this->logs.push_back(this->configName + ".json saved.");
                    this->isMapping = false;
                    this->deferredAction = nullptr;
                    step = WAIT_IR_CODE; // Reset pour la prochaine fois
                }
                break;

            default: break;
        }
    };
}


void Core::loadConfig(const std::string& configName) {
    logs.clear(); // Optionnel : on vide les anciens logs
    logs.push_back("Loading configuration: " + configName);

    if (_config.ExtractMap("configs/" + configName + ".json")) {
        for (const auto& [key, value] : _config.getMap()) {
            logs.push_back("IR Code: " + key + " -> Action: " + value);
        }
        logs.push_back("Configuration \"" + configName + "\" loaded successfully.");
    } else {
        logs.push_back("Failed to load configuration: " + configName);
    }
}

void Core::displayActions() {
    logs.clear();
    logs.push_back("Available actions:");
    logs.push_back("0. NONE");
    logs.push_back("1. STOP");
    logs.push_back("2. LEFT_CLICK");       // Mis à jour
    logs.push_back("3. RIGHT_CLICK");      // Mis à jour
    logs.push_back("4. CTRL+W (Close tab)");
    logs.push_back("5. CTRL+T (New tab)");
    logs.push_back("6. YOUTUBE");
    logs.push_back("7. TWITCH");
    logs.push_back("8. NETFLIX");
    logs.push_back("9. DISCORD");
    logs.push_back("10. ANIME");
    logs.push_back("11. VOLUME_UP");
    logs.push_back("12. VOLUME_DOWN");
    logs.push_back("13. VOLUME_MUTE");
    logs.push_back("14. PAUSE/PLAY (Space)");
    logs.push_back("15. FULLSCREEN (F)");
    logs.push_back("16. TAB_SWITCH");
    logs.push_back("17. MOUSE_UP");        // Nouveau
    logs.push_back("18. MOUSE_DOWN");      // Nouveau
    logs.push_back("19. MOUSE_LEFT");      // Nouveau
    logs.push_back("20. MOUSE_RIGHT");     // Nouveau
    logs.push_back("Please select an action by number.");
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

void Core::stopListening() {
    _stopListening = true;
    logs.push_back("Stop requested from UI.");
}

void Core::startListening(ISerialBackend* serial) {
    this->_serial = serial;  // <- on garde le pointeur pour la lambda
    _stopListening = false;

    logs.clear();
    logs.push_back("Starting to listen for IR codes...");
    logs.push_back("Listening for IR codes...");

    isMapping = true;

    deferredAction = [this]() {
        if (_stopListening) {
            logs.push_back("Listening stopped.");
            isMapping = false;
            deferredAction = nullptr;
            return;
        }
        static std::string buffer;
        char ch;

        if (_serial && _serial->readChar(ch) > 0) {
            if (ch == '\n' || ch == '\r') {
                if (!buffer.empty()) {
                    if (buffer == "IR Receiver Ready") {
                        buffer.clear();
                        return;
                    }
                    if (buffer != "0x0") {
                        const auto& map = _config.getMap();
                        auto it = map.find(buffer);
                        if (it != map.end()) {
                            logs.push_back("Executing action for: " + buffer);
                            auto action = _actions.find(it->second);
                            if (action != _actions.end()) {
                                action->second();
                            }
                        } else {
                            logs.push_back("Unknown code: " + buffer);
                        }
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    };
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

void Core::showConfig() {
    _config.showConfig(logs);
}

ISerialBackend *Core::getSerial()
{
    return _serial;
}

Core::~Core()
{
}
