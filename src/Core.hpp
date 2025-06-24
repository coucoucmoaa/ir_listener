/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

// #include "Linux.hpp"
#include "Profil.hpp"
#include "ISerialBackend.hpp"

class Core {
    public:
        Core(std::string os);
        ~Core();
        void loop();
        // void writeConfig();


    protected:
        int _serialPort = -1;;
        // Linux _linuxConfig;
        ISerialBackend* _backend;
        // Windows _windowsConfig;
        // Profil _profil;
    private:
};

#endif /* !CORE_HPP_ */
