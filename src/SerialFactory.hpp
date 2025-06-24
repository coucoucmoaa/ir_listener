/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** SerialFactory
*/

#ifndef SERIALFACTORY_HPP_
#define SERIALFACTORY_HPP_

#include "ISerialBackend.hpp"

#ifdef _WIN32
    #include "WindowsSerialBackend.hpp"
#elif defined(__linux__)
    #include "LinuxSerialBackend.hpp"
#endif

inline ISerialBackend* createSerialBackend() {
#ifdef _WIN32
    return new WindowsSerialBackend();
#elif defined(__linux__)
    return new LinuxSerialBackend();
#else
    return nullptr;
#endif
}

#endif // SERIALFACTORY_HPP_
