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

Core::Core(std::string os) {
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
    std::cout << "Listening for IR codes...\n";

    while (true) {
        if (serial->readChar(ch) > 0) {
            if (ch == '\n' || ch == '\r') {
                if (!buffer.empty()) {
                    std::cout << "Received IR code: " << buffer << std::endl;
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }

    serial->closePort();
    delete serial;
}

Core::~Core()
{
}
