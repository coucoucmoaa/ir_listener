/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** LinuxSerialBackend
*/

#ifndef LINUXSERIALBACKEND_HPP_
#define LINUXSERIALBACKEND_HPP_

#ifdef __linux__

#include "ISerialBackend.hpp"

#include <termios.h>

class LinuxSerialBackend : public ISerialBackend {
public:
    LinuxSerialBackend();
    ~LinuxSerialBackend();

    bool openPort(const std::string& portName) override;
    int readChar(char& outChar) override;
    void closePort() override;
    void makeNonBlocking();

private:
    int _serialFd;
    struct termios _tty;
};

#endif // __linux__

#endif
