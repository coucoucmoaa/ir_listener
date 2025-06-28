/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ActionButton
*/

#include "ActionButton.hpp"

ActionButton::ActionButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void ActionButton::function(Core& core, const std::string& input) const
{
    core.displayActions();
}

bool ActionButton::isClickable() const {
    return true;
}

ActionButton::~ActionButton() {
    // Destructor implementation if needed
}

bool ActionButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
