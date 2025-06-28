/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** NewConfigButton
*/

#ifndef NEWCONFIGBUTTON_HPP_
#define NEWCONFIGBUTTON_HPP_

#include "AButton.hpp"

class NewConfigButton : public AButton {
    public:
        NewConfigButton(int x, int y, int width, int height, std::string label);
        ~NewConfigButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};

#endif /* !NEWCONFIGBUTTON_HPP_ */
