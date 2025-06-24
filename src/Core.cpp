/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(std::string os)
: _linuxConfig()
{
    _serialPort = _linuxConfig.getSerialPin();
}

void Core::loop()
{
    std::string buffer;
    char ch;
    std::cout << "Listening for IR codes...\n";

    while (true) {
        int n = read(_serialPort, &ch, 1);
        if (n > 0) {
            if (ch == '\n') {
                if (!buffer.empty()) {
                    if (buffer != "0x0") {
                        std::cout << "Received IR code: " << buffer << std::endl;
                        if (buffer == "0x5010401") {
                            system("python3 src/test.py ctrl w");
                        }
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }
    close(_serialPort);
}

Core::~Core()
{
}
