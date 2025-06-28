/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ButtonFactory
*/

#include "ButtonFactory.hpp"

#include "ButtonFactory.hpp"
#include "components/NewConfigButton.hpp"
#include "components/LoadConfigButton.hpp"
#include "components/ActionButton.hpp"
// #include "components/DeleteConfigButton.hpp"
#include "components/StartButton.hpp"
#include "components/ShowConfigButton.hpp"
#include "components/ExitButton.hpp"
#include "components/DefaultButton.hpp"

std::shared_ptr<IButton> createButton(const std::string& type, int x, int y, int w, int h, const std::string& label) {
    if (type == "New Config")
        return std::make_shared<NewConfigButton>(x, y, w, h, label);
    else if (type == "Load Config")
        return std::make_shared<LoadConfigButton>(x, y, w, h, label);
    else if (type == "Exit")
        return std::make_shared<ExitButton>(x, y, w, h, label);
    else if (type == "Action")
        return std::make_shared<ActionButton>(x, y, w, h, label);
    else if (type == "Show Config")
        return std::make_shared<ShowConfigButton>(x, y, w, h, label);
    else if (type == "Start")
        return std::make_shared<StartButton>(x, y, w, h, label);
    else
        return std::make_shared<DefaultButton>(x, y, w, h, label);
}
