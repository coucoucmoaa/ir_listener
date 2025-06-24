/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** LinuxSerialBackend
*/

#ifndef LINUXSERIALBACKEND_HPP_
#define LINUXSERIALBACKEND_HPP_

#include "ISerialBackend.hpp"
#include <termios.h>

class LinuxSerialBackend : public ISerialBackend {
public:
    LinuxSerialBackend();
    ~LinuxSerialBackend();

    bool openPort(const std::string& portName) override;
    int readChar(char& outChar) override;
    void closePort() override;

private:
    int _serialFd;
    struct termios _tty;
};

#endif
