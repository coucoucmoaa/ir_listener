/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** main
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Core.hpp"
#include "UI/Ui.hpp"

int main() {
    // try {
    //     Core core = Core("linux");
    //     core.loop();
    // } catch (const std::exception &e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    //     return 1;
    // }
    Ui ui;
    ui.loop();
    return 0;
}
