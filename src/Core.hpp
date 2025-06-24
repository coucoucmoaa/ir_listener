/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Linux.hpp"
#include "Profil.hpp"

class Core {
    public:
        Core(std::string os = "Linux");
        ~Core();
        void loop();
        // void writeConfig();


    protected:
        int _serialPort = -1;;
        Linux _linuxConfig;
        // Windows _windowsConfig;
        // Profil _profil;
    private:
};

#endif /* !CORE_HPP_ */
