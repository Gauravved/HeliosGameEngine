#pragma once

#include <Helios/Core/Base.h>

namespace Helios
{
    enum class MouseButton : uint16
    {
        Unknown = 0,

        Left,
        Right,
        Middle,

        Button4,
        Button5
    };

    const char* MouseButtonToString(MouseButton button);
}