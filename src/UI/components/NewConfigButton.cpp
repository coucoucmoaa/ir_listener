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


void NewConfigButton::function(Core core) const
{
    core.loadConfig("default_config");
}

NewConfigButton::~NewConfigButton() {
    // Destructor implementation if needed
}
