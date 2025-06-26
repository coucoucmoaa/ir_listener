/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** IButton
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_
#include <raylib.h>
#include "../../Core.hpp"

class IButton {
    public:
        ~IButton() = default;
        virtual void draw() = 0;
        virtual bool isHovered() const = 0;
        virtual bool isClicked() const = 0;
        virtual void function(Core core) const = 0;
        virtual Rectangle getRectangle() const = 0;

    protected:
    private:
};

#endif /* !IBUTTON_HPP_ */
