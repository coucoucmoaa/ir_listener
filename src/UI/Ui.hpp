/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Ui
*/

#ifndef UI_HPP_
#define UI_HPP_

#include "components/IButton.hpp"
#include "../Core.hpp"
#include <vector>
#include <memory>

class Ui {
    public:
        Ui();
        ~Ui();
        void loop();

    protected:
    private:
        std::vector<std::shared_ptr<IButton>> _buttons;
        Vector2 _mouse;
        int _width;
        int _height;
        Core _core;
};

#endif /* !UI_HPP_ */
