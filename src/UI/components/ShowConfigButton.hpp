/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ShowConfigButton
*/

#ifndef SHOWCONFIGBUTTON_HPP_
#define SHOWCONFIGBUTTON_HPP_

#include "AButton.hpp"

class ShowConfigButton : public AButton {
    public:
        ShowConfigButton(int x, int y, int width, int height, std::string label);
        ~ShowConfigButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};

#endif /* !SHOWCONFIGBUTTON_HPP_ */
