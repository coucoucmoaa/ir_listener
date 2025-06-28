/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** DefaultButton
*/

#ifndef DEFAULTBUTTON_HPP_
#define DEFAULTBUTTON_HPP_

#include "AButton.hpp"

class DefaultButton : public AButton {
    public:
        DefaultButton(int x, int y, int width, int height, std::string label);
        ~DefaultButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override; // DefaultButton does not trigger a textbox
    protected:
    private:
};

#endif /* !DEFAULTBUTTON_HPP_ */
