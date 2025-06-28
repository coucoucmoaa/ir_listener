/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** ButtonFactory
*/

#ifndef BUTTONFACTORY_HPP_
#define BUTTONFACTORY_HPP_

#include <memory>
#include <string>
#include "components/IButton.hpp"

std::shared_ptr<IButton> createButton(const std::string& type, int x, int y, int w, int h, const std::string& label);
#endif /* !BUTTONFACTORY_HPP_ */
