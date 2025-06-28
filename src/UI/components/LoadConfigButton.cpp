/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** LoadConfigButton
*/

#include "LoadConfigButton.hpp"

LoadConfigButton::LoadConfigButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void LoadConfigButton::function(Core& core, const std::string& input) const
{
    // core.createConfig(core.getSerial(), input);
    std::cout << input << std::endl;
    core.loadConfig(input);
}

bool LoadConfigButton::isClickable() const {
    return true;
}

LoadConfigButton::~LoadConfigButton() {
    // Destructor implementation if needed
}

bool LoadConfigButton::isTextBox() const {
    return true; // This button triggers a textbox for input
}
