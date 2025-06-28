/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** StartButton
*/

#include "StartButton.hpp"

StartButton::StartButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void StartButton::function(Core& core, const std::string& input) const
{
    core.startListening(core.getSerial());
    // std::cout << "coucou " << input << std::endl;
}

bool StartButton::isClickable() const {
    return true;
}

StartButton::~StartButton() {
    // Destructor implementation if needed
}

bool StartButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
