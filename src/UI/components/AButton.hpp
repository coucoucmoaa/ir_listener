/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** AButton
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "../../RaylibSafe.hpp"
#include <string>
#include "IButton.hpp"

class AButton : public IButton {
    public:
        AButton() = default;
        ~AButton() = default;
        void draw() override;
        bool isHovered() const override;
        bool isClicked() const override;
        Rectangle getRectangle() const override;
        virtual void function(Core& core, const std::string& input = "") const override;
        virtual bool isClickable() const override;
        std::string getLabel() const override;
        virtual bool isTextBox() const override;
        // const char* getLabel() const;
    protected:
        int _x;
        int _y;
        int _width;
        int _height;
        std::string _label;
};
#endif /* !AButton_HPP_ */
