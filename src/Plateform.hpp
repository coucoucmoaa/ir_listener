/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** Plateform
*/

#ifndef PLATEFORM_HPP_
#define PLATEFORM_HPP_

#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

// Check if NOMINMAX is already defined to avoid redefinition warning
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Undefine these before including windows.h to avoid conflicts with raylib
#ifdef Rectangle
#undef Rectangle
#endif
#ifdef CloseWindow
#undef CloseWindow
#endif
#ifdef ShowCursor
#undef ShowCursor
#endif
#ifdef LoadImage
#undef LoadImage
#endif
#ifdef DrawText
#undef DrawText
#endif

#include <windows.h>
#include <shellapi.h>

// After including windows.h, undefine the conflicting macros/functions
#undef Rectangle
#undef CloseWindow  
#undef ShowCursor
#undef LoadImage
#undef DrawText
#undef DrawTextEx

#endif
#endif /* !PLATEFORM_HPP_ */
