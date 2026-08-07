#pragma once

#include <Helios/Core/Base.h>

namespace Helios
{
    enum class KeyCode : uint16
    {
        Unknown = 0,

        // Alphabet
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        // Numbers
        D0,
        D1,
        D2,
        D3,
        D4,
        D5,
        D6,
        D7,
        D8,
        D9,

        // Function Keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        // Arrow Keys
        Left,
        Right,
        Up,
        Down,

        // Modifier Keys
        LeftShift,
        RightShift,
        LeftControl,
        RightControl,
        LeftAlt,
        RightAlt,

        // Common Keys
        Space,
        Enter,
        Escape,
        Tab,
        Backspace,
        Delete,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,

        // Lock Keys
        CapsLock,
        NumLock,
        ScrollLock,

        // Print / Pause
        PrintScreen,
        Pause,

        // Numpad
        NumPad0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,

        NumPadMultiply,
        NumPadAdd,
        NumPadSubtract,
        NumPadDecimal,
        NumPadDivide,

        Menu
    };

    const char* KeyCodeToString(KeyCode key);
}