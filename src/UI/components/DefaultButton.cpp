/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** DefaultButton
*/

#include "DefaultButton.hpp"

DefaultButton::DefaultButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void DefaultButton::function(Core&core, const std::string& input) const
{
    (void)core;
}

bool DefaultButton::isClickable() const {
    return false;
}

DefaultButton::~DefaultButton() {
    // Destructor implementation if needed
}

bool DefaultButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
