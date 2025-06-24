/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** WindowsSerialBackend
*/

#ifndef WINDOWSSERIALBACKEND_HPP_
#define WINDOWSSERIALBACKEND_HPP_

#include "ISerialBackend.hpp"
#ifdef _WIN32
#include <windows.h>
#endif
#include <string>

class WindowsSerialBackend : public ISerialBackend {
public:
    WindowsSerialBackend(const std::string& port);
    ~WindowsSerialBackend();

    bool openPort(const std::string& portName) override;
    int readChar(char& outChar) override;
    void closePort() override;

private:
    #ifdef _WIN32
    HANDLE hSerial;
    #endif
    std::string _portName;
};

#endif /* !WINDOWSSERIALBACKEND_HPP_ */
