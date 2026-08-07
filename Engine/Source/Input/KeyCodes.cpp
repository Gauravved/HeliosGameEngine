#include <Helios/Input/KeyCodes.h>

#include <array>

namespace
{
    using namespace Helios;

    constexpr std::array<const char*, static_cast<size_t>(KeyCode::Menu) + 1> s_KeyNames =
    {
        "Unknown",

        // Alphabet
        "A","B","C","D","E","F","G","H","I","J","K","L","M",
        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z",

        // Numbers
        "D0","D1","D2","D3","D4","D5","D6","D7","D8","D9",

        // Function Keys
        "F1","F2","F3","F4","F5","F6",
        "F7","F8","F9","F10","F11","F12",

        // Arrow Keys
        "Left",
        "Right",
        "Up",
        "Down",

        // Modifiers
        "LeftShift",
        "RightShift",
        "LeftControl",
        "RightControl",
        "LeftAlt",
        "RightAlt",

        // Common
        "Space",
        "Enter",
        "Escape",
        "Tab",
        "Backspace",
        "Delete",
        "Insert",
        "Home",
        "End",
        "PageUp",
        "PageDown",

        // Locks
        "CapsLock",
        "NumLock",
        "ScrollLock",

        // Print/Pause
        "PrintScreen",
        "Pause",

        // Numpad
        "NumPad0",
        "NumPad1",
        "NumPad2",
        "NumPad3",
        "NumPad4",
        "NumPad5",
        "NumPad6",
        "NumPad7",
        "NumPad8",
        "NumPad9",

        "NumPadMultiply",
        "NumPadAdd",
        "NumPadSubtract",
        "NumPadDecimal",
        "NumPadDivide",

        "Menu"
    };
}

namespace Helios
{
    const char* KeyCodeToString(KeyCode keyCode)
    {
        return s_KeyNames[static_cast<size_t>(keyCode)];
    }
}