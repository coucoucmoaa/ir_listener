/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ExitButton
*/

#include "ExitButton.hpp"

ExitButton::ExitButton(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
    }


void ExitButton::function(Core& core, const std::string& input) const
{
    core.logs.push_back("Exiting program...");
    CloseWindow();  // Ferme proprement la fenêtre Raylib
    exit(0); 
}

bool ExitButton::isClickable() const {
    return true;
}

ExitButton::~ExitButton() {
    // Destructor implementation if needed
}

bool ExitButton::isTextBox() const {
    return false; // This button triggers a textbox for input
}
