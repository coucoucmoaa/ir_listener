/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** TextBox
*/

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_
#include "../../RaylibSafe.hpp"
#include <string>

class TextBox {
    public:
        Rectangle box;
        std::string text;
        bool active;
        int fontSize;
        bool justOpenedTextbox = false;
        std::string label; 

        TextBox(float x, float y, float w, float h, std::string labelText = "");
        ~TextBox();
        void update();
        void draw() const;
        void updateSize();
        bool isMouseInside() const;
        void justOpenTextBox(bool value) {
            justOpenedTextbox = value;
        }


    protected:
    private:
};

#endif /* !TEXTBOX_HPP_ */
