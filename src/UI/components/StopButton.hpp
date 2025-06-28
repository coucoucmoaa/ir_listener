/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** StopButton
*/

#ifndef STOPBUTTON_HPP_
#define STOPBUTTON_HPP_

#include "AButton.hpp"

class StopButton : public AButton {
    public:
        StopButton(int x, int y, int width, int height, std::string label);
        ~StopButton();
        void function(Core& core, const std::string& input = "") const override;
        bool isClickable() const override;
        bool isTextBox() const override;
    protected:
    private:
};

#endif /* !STOPBUTTON_HPP_ */
