/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Ui
*/

#include "Ui.hpp"
#include <iostream>
#include <raylib.h>
#include <unordered_map>
#include "components/NewConfigButton.hpp"

Ui::Ui() : _mouse(), _width(800), _height(600), _core("linux")
{

    std::unordered_map<std::string, std::string> map = {
        {"Button 1", "New Config"},
        {"Button 2", "Action"},
        {"Button 3", "Load Config"},
        {"Button 4", "Show Config"},
        {"Button 5", "Start"},
        {"Button 6", "Stop"},
        {"Button 7", "Exit"}
    };
    int maxHeight = _height - 50;
    int buttonWidth = 150;
    int buttonHeight = 50;
    int spacingY = 10;
    int spacingX = 30;

    int x = spacingX;
    int y = spacingY;

    for (int i = 0; i < 7; ++i) {
        if (y + buttonHeight > maxHeight) {
            y = spacingY;
            x += buttonWidth + spacingX;
        }

        std::string label = map["Button " + std::to_string(i + 1)];
        _buttons.push_back(std::make_shared<NewConfigButton>(x, y, buttonWidth, buttonHeight, label));
        y += buttonHeight + spacingY;
    }
    InitWindow(_width, _height, "Ir_receiver");
    SetTargetFPS(60);
}

void Ui::loop()
{
    while (!WindowShouldClose())  // Ferme avec ESC ou la croix
    {


        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(auto &button : _buttons) {
            button->draw();
            if (button->isClicked()) {
                button->function(_core);
                std::cout << "Button clicked!" << std::endl;
            }
        }

        EndDrawing();
    }
}

Ui::~Ui()
{
    CloseWindow();
}
