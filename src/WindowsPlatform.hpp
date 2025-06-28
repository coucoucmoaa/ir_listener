/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** WindowsPlatform - Windows-specific functionality without raylib conflicts
*/

#ifndef WINDOWSPLATFORM_HPP_
#define WINDOWSPLATFORM_HPP_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <shellapi.h>

#endif

#endif /* !WINDOWSPLATFORM_HPP_ */
