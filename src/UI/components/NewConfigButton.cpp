/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** NewConfigButton
*/

#include "NewConfigButton.hpp"

NewConfigButton::NewConfigButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void NewConfigButton::function(Core& core, const std::string& input) const
{
    core.createConfig(core.getSerial(), input);
    // std::cout << input << std::endl;
}

bool NewConfigButton::isClickable() const {
    return true;
}

NewConfigButton::~NewConfigButton() {
    // Destructor implementation if needed
}

bool NewConfigButton::isTextBox() const {
    return true; // This button triggers a textbox for input
}
