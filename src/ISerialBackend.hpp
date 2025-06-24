/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ISerialBackend
*/

#ifndef ISERIALBACKEND_HPP_
#define ISERIALBACKEND_HPP_

#include <string>

class ISerialBackend {
public:
    virtual ~ISerialBackend() = default;
    // virtual bool readLine(std::string& buffer) = 0; // lit une ligne complète (finie par \n)
    virtual bool openPort(const std::string& portName) = 0;
    virtual int readChar(char& outChar) = 0;
    virtual void closePort() = 0;
};

#endif /* !ISERIALBACKEND_HPP_ */
