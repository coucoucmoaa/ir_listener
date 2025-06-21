/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** main
*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Profil.hpp"

const char* SERIAL_PORT = "/dev/ttyUSB0"; // Change if needed
const int BAUD_RATE = B9600;

int main() {
    Profil profil("Test Profil");
    int serialPort = open(SERIAL_PORT, O_RDONLY | O_NOCTTY);
    if (serialPort < 0) {
        perror("Error opening serial port");
        return 1;
    }

    struct termios tty{};
    if (tcgetattr(serialPort, &tty) != 0) {
        perror("tcgetattr failed");
        return 1;
    }

    cfsetispeed(&tty, BAUD_RATE);
    cfsetospeed(&tty, BAUD_RATE);

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

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        perror("tcsetattr failed");
        return 1;
    }

    std::string buffer;
    char ch;
    std::cout << "Listening for IR codes...\n";

    while (true) {
        int n = read(serialPort, &ch, 1);
        if (n > 0) {
            if (ch == '\n') {
                if (!buffer.empty()) {
                    if (buffer != "0x0") {
                        std::cout << "Received IR code: " << buffer << std::endl;
                    }
                    buffer.clear();
                }
            } else if (isprint(ch)) {
                buffer += ch;
            }
        }
    }
    close(serialPort);
    return 0;
}
