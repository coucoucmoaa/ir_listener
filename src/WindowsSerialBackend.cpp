#ifdef _WIN32
#include "WindowsSerialBackend.hpp"
#include <iostream>

WindowsSerialBackend::WindowsSerialBackend()
    : _hSerial(INVALID_HANDLE_VALUE) {}

WindowsSerialBackend::~WindowsSerialBackend() {
    closePort();
}

bool WindowsSerialBackend::openPort(const std::string& portName) {
    _hSerial = CreateFileA(portName.c_str(),
                           GENERIC_READ,
                           0,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);

    if (_hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening port: " << portName << std::endl;
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(_hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial parameters.\n";
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(_hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial parameters.\n";
        return false;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    SetCommTimeouts(_hSerial, &timeouts);

    return true;
}

int WindowsSerialBackend::readChar(char& outChar) {
    DWORD bytesRead;
    if (!ReadFile(_hSerial, &outChar, 1, &bytesRead, NULL)) {
        std::cerr << "ReadFile failed.\n";
        return -1;
    }
    return bytesRead;
}

void WindowsSerialBackend::closePort() {
    if (_hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(_hSerial);
        _hSerial = INVALID_HANDLE_VALUE;
    }
}
#endif
