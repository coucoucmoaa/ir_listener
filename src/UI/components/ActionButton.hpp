/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ActionButton
*/

#ifndef ACTIONBUTTON_HPP_
#define ACTIONBUTTON_HPP_

#include "AButton.hpp"

class ActionButton : public AButton {
    public:
        ActionButton(int x, int y, int width, int height, std::string label);
        ~ActionButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};
#endif /* !ACTIONBUTTON_HPP_ */
