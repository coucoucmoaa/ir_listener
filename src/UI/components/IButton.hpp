/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** IButton
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_
#include "../../RaylibSafe.hpp"
#include "../../Core.hpp"

class IButton {
    public:
        ~IButton() = default;
        virtual void draw() = 0;
        virtual bool isHovered() const = 0;
        virtual bool isClicked() const = 0;
        virtual void function(Core& core, const std::string& input = "") const = 0;
        virtual Rectangle getRectangle() const = 0;
        virtual bool isClickable() const = 0;
        virtual std::string getLabel() const = 0;
        virtual bool isTextBox() const = 0; // Indique si le bouton déclenche une textbox
    protected:
    private:
};

#endif /* !IBUTTON_HPP_ */
