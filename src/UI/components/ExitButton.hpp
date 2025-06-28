/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ExitButton
*/

#ifndef EXITBUTTON_HPP_
#define EXITBUTTON_HPP_

#include "AButton.hpp"

class ExitButton : public AButton {
    public:
        ExitButton(int x, int y, int width, int height, std::string label);
        ~ExitButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};

#endif /* !EXITBUTTON_HPP_ */
