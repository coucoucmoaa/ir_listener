/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** WindowsSerialBackend
*/

#ifndef WINDOWSSERIALBACKEND_HPP_
#define WINDOWSSERIALBACKEND_HPP_

#include "ISerialBackend.hpp"
#include <string>
#include <vector>

// Forward declarations to avoid including Windows headers in header file
#ifdef _WIN32
using HANDLE = void*;
#endif

class WindowsSerialBackend : public ISerialBackend {
public:
    WindowsSerialBackend();
    explicit WindowsSerialBackend(const std::string& port);
    ~WindowsSerialBackend();

    bool openPort(const std::string& portName) override;
    int readChar(char& outChar) override;
    void closePort() override;

private:
    #ifdef _WIN32
    HANDLE _hSerial;
    #endif
    std::string _portName;
};

#endif /* !WINDOWSSERIALBACKEND_HPP_ */
