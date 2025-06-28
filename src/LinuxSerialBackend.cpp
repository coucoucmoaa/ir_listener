/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** LinuxSerialBackend
*/

#include "LinuxSerialBackend.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

LinuxSerialBackend::LinuxSerialBackend() : _serialFd(-1) {}

LinuxSerialBackend::~LinuxSerialBackend() {
    closePort();
}

void LinuxSerialBackend::makeNonBlocking() {
    int flags = fcntl(_serialFd, F_GETFL, 0);
    if (flags == -1) return; // gestion d'erreur
    fcntl(_serialFd, F_SETFL, flags | O_NONBLOCK);
}

bool LinuxSerialBackend::openPort(const std::string& portName) {
    _serialFd = open(portName.c_str(), O_RDONLY | O_NOCTTY);
    if (_serialFd < 0) {
        std::cerr << "Error opening port: " << strerror(errno) << std::endl;
        return false;
    }
    
    tcgetattr(_serialFd, &_tty);
    cfsetispeed(&_tty, B9600);
    cfsetospeed(&_tty, B9600);
    _tty.c_cflag &= ~PARENB;
    _tty.c_cflag &= ~CSTOPB;
    _tty.c_cflag &= ~CSIZE;
    _tty.c_cflag |= CS8;
    _tty.c_cflag &= ~CRTSCTS;
    _tty.c_cflag |= CREAD | CLOCAL;
    _tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    _tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    _tty.c_oflag &= ~OPOST;
    _tty.c_cc[VMIN] = 1;
    _tty.c_cc[VTIME] = 0;
    tcsetattr(_serialFd, TCSANOW, &_tty);
    makeNonBlocking();
    return true;
}

int LinuxSerialBackend::readChar(char& outChar) {
    ssize_t result = read(_serialFd, &outChar, 1);
    if (result > 0)
        return 1; // un caractère lu
    return -1; 
}

void LinuxSerialBackend::closePort() {
    if (_serialFd != -1) {
        close(_serialFd);
        _serialFd = -1;
    }
}
