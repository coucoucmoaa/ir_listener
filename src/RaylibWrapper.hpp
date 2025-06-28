/*
** EPITECH PROJECT, 2025
** hub_ir
** File description:
** RaylibWrapper - Wrapper to handle Windows/Raylib conflicts
*/

#ifndef RAYLIBWRAPPER_HPP_
#define RAYLIBWRAPPER_HPP_

#ifdef _WIN32
// Include windows.h first and save the functions we need
#include "Plateform.hpp"

// Save Windows functions with different names
#define Win32CloseWindow ::CloseWindow
#define Win32ShowCursor ::ShowCursor
#define Win32LoadImageA ::LoadImageA
#define Win32DrawTextA ::DrawTextA
#define Win32DrawTextExA ::DrawTextExA

// Now undefine the conflicting names
#pragma push_macro("CloseWindow")
#pragma push_macro("ShowCursor")
#pragma push_macro("LoadImage")
#pragma push_macro("DrawText")
#pragma push_macro("DrawTextEx")

#undef CloseWindow
#undef ShowCursor
#undef LoadImage
#undef DrawText
#undef DrawTextEx
#endif

// Now include raylib safely
#include <raylib.h>

#ifdef _WIN32
// Restore the macros if needed later
#pragma pop_macro("CloseWindow")
#pragma pop_macro("ShowCursor") 
#pragma pop_macro("LoadImage")
#pragma pop_macro("DrawText")
#pragma pop_macro("DrawTextEx")
#endif

#endif // RAYLIBWRAPPER_HPP_
