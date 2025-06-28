/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** StopButton
*/

#include "StopButton.hpp"

StopButton::StopButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void StopButton::function(Core& core, const std::string& input) const
{
    core.stopListening();
    // std::cout << "coucou " << input << std::endl;
}

bool StopButton::isClickable() const {
    return true;
}

StopButton::~StopButton() {
    // Destructor implementation if needed
}

bool StopButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
