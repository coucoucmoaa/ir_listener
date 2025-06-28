/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** StartButton
*/

#ifndef STARTBUTTON_HPP_
#define STARTBUTTON_HPP_

#include "AButton.hpp"

class StartButton : public AButton {
    public:
        StartButton(int x, int y, int width, int height, std::string label);
        ~StartButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};


#endif /* !STARTBUTTON_HPP_ */
