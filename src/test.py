
#!/usr/bin/env python3

import serial
import pyautogui
import sys

args = sys.argv[1:]
if not args:
    sys.exit("Usage: python3 keyboard_action.py <key> [<modifier>]")

if len(args) == 1:
    pyautogui.press(args[0])
else:
    pyautogui.hotkey(*args)
