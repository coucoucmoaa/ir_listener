/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** LoadConfigButton
*/

#ifndef LOADCONFIGBUTTON_HPP_
#define LOADCONFIGBUTTON_HPP_

#include "AButton.hpp"

class LoadConfigButton : public AButton {
    public:
        LoadConfigButton(int x, int y, int width, int height, std::string label);
        ~LoadConfigButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};


#endif /* !LOADCONFIGBUTTON_HPP_ */
