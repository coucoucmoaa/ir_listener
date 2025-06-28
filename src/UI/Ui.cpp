/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Ui
*/

#include "Ui.hpp"
#include <iostream>
#include "../RaylibSafe.hpp"
#include <unordered_map>
#include "ButtonFactory.hpp"
#include "components/TextBox.hpp"

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

        std::string labelKey = "Button " + std::to_string(i + 1);
    std::string label = map[labelKey];
    _buttons.push_back(createButton(label, x, y, buttonWidth, buttonHeight, label));
        y += buttonHeight + spacingY;
    }
    InitWindow(_width, _height, "Ir_receiver");
    SetTargetFPS(60);
}

std::unique_ptr<TextBox> activeTextbox = nullptr;
std::shared_ptr<IButton> clickedButton = nullptr;
InputContext inputContext = InputContext::None;


void Ui::loop()
{
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dessin et gestion des boutons
        for (auto& button : _buttons) {
            button->draw();

            if (button->isClicked() && button->isClickable()) {
                if (button->isTextBox()) {
                    std::string label = (button->getLabel() == "New Config")
                        ? "Enter Config name:" : "Input text:";

                    activeTextbox = std::make_unique<TextBox>(100, 100, 300, 40, label);
                    clickedButton = button;
                    activeTextbox->justOpenTextBox(true);
                    inputContext = InputContext::ButtonClick;
                } else {
                    button->function(_core);
                }
            }
        }

        // Si on attend une saisie d'action (ex: après mapping IR)
        if (_core.isWaitingForInput && !activeTextbox) {
            activeTextbox = std::make_unique<TextBox>(100, 100, 300, 40, "Enter action name:");
            activeTextbox->justOpenTextBox(true);
            inputContext = InputContext::ActionName;
        }

        // Gestion unique textbox
        if (activeTextbox) {
            activeTextbox->update();
            activeTextbox->draw();

            // Validation avec Enter
            if (IsKeyPressed(KEY_ENTER)) {
                if (inputContext == InputContext::ButtonClick && clickedButton) {
                    clickedButton->function(_core, activeTextbox->text);
                    clickedButton.reset();
                } else if (inputContext == InputContext::ActionName) {
                    _core.inputActionName = activeTextbox->text;
                    _core.isWaitingForInput = false;
                }
                activeTextbox.reset();
            }

            // Clic en dehors pour fermer textbox
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                !activeTextbox->isMouseInside() &&
                !activeTextbox->justOpenedTextbox) {
                activeTextbox.reset();
                clickedButton.reset();
                _core.isWaitingForInput = false;
            }

            if (activeTextbox && activeTextbox->justOpenedTextbox) {
                activeTextbox->justOpenTextBox(false);
            }
        }

        if (_core.isMapping && _core.deferredAction) {
            _core.deferredAction(); // exécution incrémentale
        }

        // Affichage des logs graphiques sur la moitié droite
        Color terminalBackground = { 230, 230, 230, 255 }; // gris doux
        DrawRectangle(_width / 2, 0, _width / 2, _height, terminalBackground);

        DrawText("Log Output", _width / 2 + 20, 10, 22, BLACK);

        float logX = _width / 2 + 20;
        float logY = 40;
        int fontSize = 20;
        int lineSpacing = fontSize + 4;

        for (const auto& msg : _core.logs) {
            DrawText(msg.c_str(), logX, logY, fontSize, DARKGRAY);
            logY += lineSpacing;
        }

        EndDrawing();
    }
}


Ui::~Ui()
{
    CloseWindow();
}
