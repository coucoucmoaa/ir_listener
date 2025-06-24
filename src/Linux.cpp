/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Linux
*/

#include "Linux.hpp"
#include <cstring>
#include <cerrno> 

Linux::Linux()
{
    LinuxInit();
}

void Linux::LinuxInit()
{
    _serialPin = open(_SERIAL_PORT, O_RDONLY | O_NOCTTY);
    if (_serialPin < 0) {
        std::cerr << "Error opening serial port " << _SERIAL_PORT << ": " << strerror(errno) << std::endl;
        return;
    }

    struct termios tty{};
    if (tcgetattr(_serialPin, &tty) != 0) {
        std::cerr << "Error getting attributes for serial port " << _SERIAL_PORT << ": " << strerror(errno) << std::endl;
        return;
    }

    cfsetispeed(&tty, _BAUD_RATE);
    cfsetospeed(&tty, _BAUD_RATE);

    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(_serialPin, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting attributes for serial port " << _SERIAL_PORT << ": " << strerror(errno) << std::endl;
        return;
    }
}

int Linux::getSerialPin()
{
    return _serialPin;
}

Linux::~Linux()
{
}
