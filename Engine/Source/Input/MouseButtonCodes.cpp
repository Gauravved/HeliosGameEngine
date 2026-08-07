#include<Helios/Input/MouseButtonCodes.h>

#include <array>

namespace
{
    using namespace Helios;

    constexpr std::array<const char*, static_cast<size_t>(MouseButton::Button5) + 1> s_ButtonNames =
    {
        "Unknown",

        "Left",
        "Right",
        "Middle",
        "Button4",
        "Button5"
    };
}

namespace Helios
{
    const char* MouseButtonToString(MouseButton button)
    {
        return s_ButtonNames[static_cast<size_t>(button)];
    }
}