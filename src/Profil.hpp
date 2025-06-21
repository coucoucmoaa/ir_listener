/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** profil
*/

#ifndef PROFIL_HPP_
#define PROFIL_HPP_

#include <vector>
#include <iostream>

class Config {
    private:
        std::string _name;
        std::vector<std::string> _codes;
};

class Profil {
    public:
        Profil(std::string name);
        ~Profil();
    private:
        std::string _name;
        std::vector<Config> _configs;
};


#endif /* !PROFIL_HPP_ */
