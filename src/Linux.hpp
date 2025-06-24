/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Linux
*/

#ifndef LINUX_HPP_
#define LINUX_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Linux {
    public:
        Linux();
        ~Linux();
        int getSerialPin();

    protected:
    private:
        void LinuxInit();
        int _serialPin;
        const char* _SERIAL_PORT = "/dev/ttyUSB0";
        const int _BAUD_RATE = B9600;

};

#endif /* !LINUX_HPP_ */
