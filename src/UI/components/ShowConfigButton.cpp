/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ShowConfigButton
*/

#include "ShowConfigButton.hpp"

ShowConfigButton::ShowConfigButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void ShowConfigButton::function(Core& core, const std::string& input) const
{
    core.showConfig();
    // std::cout << "Showing configuration: " << input << std::endl;
}

bool ShowConfigButton::isClickable() const {
    return true;
}

ShowConfigButton::~ShowConfigButton() {
    // Destructor implementation if needed
}

bool ShowConfigButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
