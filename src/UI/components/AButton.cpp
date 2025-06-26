/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** button
*/

#include "AButton.hpp"
#include <iostream>
#include <raylib.h>

void AButton::draw() {
    Vector2 position = { static_cast<float>(_x), static_cast<float>(_y) };
    Rectangle buttonRect = { position.x, position.y, static_cast<float>(_width), static_cast<float>(_height) };
    
    if (isHovered()) {
        DrawRectangleRec(buttonRect, SKYBLUE);
    } else {
        DrawRectangleRec(buttonRect, LIGHTGRAY);
    }
    
    DrawText(_label.c_str(), _x + 10, _y + 10, 20, BLACK);
}

bool AButton::isHovered() const {
    Vector2 mousePos = GetMousePosition();
    Rectangle buttonRect = { static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_width), static_cast<float>(_height) };
    return CheckCollisionPointRec(mousePos, buttonRect);
}

bool AButton::isClicked() const {
    return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

Rectangle AButton::getRectangle() const {
    return { static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_width), static_cast<float>(_height) };
}

void AButton::function(Core core) const
{
    std::cout << "Button clicked: " << _label << std::endl;
}
