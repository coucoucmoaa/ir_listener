/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** TextBox
*/

#include "TextBox.hpp"

TextBox::TextBox(float x, float y, float w, float h, std::string labelText)
: box{ x, y, w, h }, text(""), label(labelText), active(true), fontSize(20) {}

void TextBox::update() {
    if (!active) return;
    
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125 && text.length() < 20) {
            text += static_cast<char>(key);
            updateSize();
        }
        key = GetCharPressed();
    }
    
    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
            text.pop_back();
            updateSize();  // also resize after removing char
        }
}

void TextBox::draw() const {
    if (!label.empty()) {
        DrawText(label.c_str(), box.x, box.y - fontSize - 5, fontSize, DARKGRAY);
    }
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 1, DARKGRAY);
    DrawText(text.c_str(), box.x + 5, box.y + 8, fontSize, BLACK);
}

void TextBox::updateSize()
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    const float padding = 10.0f;

    // Resize if text is wider than box
    if (textWidth + padding > box.width) {
        box.width = textWidth + padding;
    }
}

bool TextBox::isMouseInside() const {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, box);
}

TextBox::~TextBox()
{
}
    