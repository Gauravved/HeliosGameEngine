#include<Windows.h>
#include<array>

#include<Helios/Platform/Windows/WindowsKeyMap.h>



namespace
{
    constexpr size_t MaxVirtualKeys = 256;
    constexpr size_t KeyCount = static_cast<size_t>(Helios::KeyCode::Menu) + 1;

    std::array<Helios::KeyCode, MaxVirtualKeys> CreateKeyMap()
    {
        std::array<Helios::KeyCode, MaxVirtualKeys> map{};

        // Fill every entry with Unknown
        map.fill(Helios::KeyCode::Unknown);

        // Alphabet
        map['A'] = Helios::KeyCode::A;
        map['B'] = Helios::KeyCode::B;
        map['C'] = Helios::KeyCode::C;
        map['D'] = Helios::KeyCode::D;
        map['E'] = Helios::KeyCode::E;
        map['F'] = Helios::KeyCode::F;
        map['G'] = Helios::KeyCode::G;
        map['H'] = Helios::KeyCode::H;
        map['I'] = Helios::KeyCode::I;
        map['J'] = Helios::KeyCode::J;
        map['K'] = Helios::KeyCode::K;
        map['L'] = Helios::KeyCode::L;
        map['M'] = Helios::KeyCode::M;
        map['N'] = Helios::KeyCode::N;
        map['O'] = Helios::KeyCode::O;
        map['P'] = Helios::KeyCode::P;
        map['Q'] = Helios::KeyCode::Q;
        map['R'] = Helios::KeyCode::R;
        map['S'] = Helios::KeyCode::S;
        map['T'] = Helios::KeyCode::T;
        map['U'] = Helios::KeyCode::U;
        map['V'] = Helios::KeyCode::V;
        map['W'] = Helios::KeyCode::W;
        map['X'] = Helios::KeyCode::X;
        map['Y'] = Helios::KeyCode::Y;
        map['Z'] = Helios::KeyCode::Z;

        // Number row
        map['0'] = Helios::KeyCode::D0;
        map['1'] = Helios::KeyCode::D1;
        map['2'] = Helios::KeyCode::D2;
        map['3'] = Helios::KeyCode::D3;
        map['4'] = Helios::KeyCode::D4;
        map['5'] = Helios::KeyCode::D5;
        map['6'] = Helios::KeyCode::D6;
        map['7'] = Helios::KeyCode::D7;
        map['8'] = Helios::KeyCode::D8;
        map['9'] = Helios::KeyCode::D9;

        //Symbols
        map[VK_OEM_3] = Helios::KeyCode::GraveAccent;
        map[VK_OEM_MINUS] = Helios::KeyCode::Minus;
        map[VK_OEM_PLUS] = Helios::KeyCode::Equal;
        map[VK_OEM_4] = Helios::KeyCode::LeftBracket;
        map[VK_OEM_6] = Helios::KeyCode::RightBracket;
        map[VK_OEM_5] = Helios::KeyCode::Backslash;
        map[VK_OEM_1] = Helios::KeyCode::Semicolon;
        map[VK_OEM_7] = Helios::KeyCode::Apostrophe;
        map[VK_OEM_COMMA] = Helios::KeyCode::Comma;
        map[VK_OEM_PERIOD] = Helios::KeyCode::Period;
        map[VK_OEM_2] = Helios::KeyCode::Slash;

        // Function Keys
        map[VK_F1] = Helios::KeyCode::F1;
        map[VK_F2] = Helios::KeyCode::F2;
        map[VK_F3] = Helios::KeyCode::F3;
        map[VK_F4] = Helios::KeyCode::F4;
        map[VK_F5] = Helios::KeyCode::F5;
        map[VK_F6] = Helios::KeyCode::F6;
        map[VK_F7] = Helios::KeyCode::F7;
        map[VK_F8] = Helios::KeyCode::F8;
        map[VK_F9] = Helios::KeyCode::F9;
        map[VK_F10] = Helios::KeyCode::F10;
        map[VK_F11] = Helios::KeyCode::F11;
        map[VK_F12] = Helios::KeyCode::F12;

        // Common
        map[VK_SPACE] = Helios::KeyCode::Space;
        map[VK_RETURN] = Helios::KeyCode::Enter;
        map[VK_ESCAPE] = Helios::KeyCode::Escape;
        map[VK_TAB] = Helios::KeyCode::Tab;
        map[VK_BACK] = Helios::KeyCode::Backspace;
        map[VK_DELETE] = Helios::KeyCode::Delete;
        map[VK_INSERT] = Helios::KeyCode::Insert;
        map[VK_HOME] = Helios::KeyCode::Home;
        map[VK_END] = Helios::KeyCode::End;
        map[VK_PRIOR] = Helios::KeyCode::PageUp;
        map[VK_NEXT] = Helios::KeyCode::PageDown;

        // Arrow Keys
        map[VK_LEFT] = Helios::KeyCode::Left;
        map[VK_RIGHT] = Helios::KeyCode::Right;
        map[VK_UP] = Helios::KeyCode::Up;
        map[VK_DOWN] = Helios::KeyCode::Down;

        // Modifiers
        map[VK_LSHIFT] = Helios::KeyCode::LeftShift;
        map[VK_RSHIFT] = Helios::KeyCode::RightShift;
        map[VK_LCONTROL] = Helios::KeyCode::LeftControl;
        map[VK_RCONTROL] = Helios::KeyCode::RightControl;
        map[VK_LMENU] = Helios::KeyCode::LeftAlt;
        map[VK_RMENU] = Helios::KeyCode::RightAlt;

        // Locks
        map[VK_CAPITAL] = Helios::KeyCode::CapsLock;
        map[VK_NUMLOCK] = Helios::KeyCode::NumLock;
        map[VK_SCROLL] = Helios::KeyCode::ScrollLock;

        // Print/Pause
        map[VK_SNAPSHOT] = Helios::KeyCode::PrintScreen;
        map[VK_PAUSE] = Helios::KeyCode::Pause;

        // Numpad
        map[VK_NUMPAD0] = Helios::KeyCode::NumPad0;
        map[VK_NUMPAD1] = Helios::KeyCode::NumPad1;
        map[VK_NUMPAD2] = Helios::KeyCode::NumPad2;
        map[VK_NUMPAD3] = Helios::KeyCode::NumPad3;
        map[VK_NUMPAD4] = Helios::KeyCode::NumPad4;
        map[VK_NUMPAD5] = Helios::KeyCode::NumPad5;
        map[VK_NUMPAD6] = Helios::KeyCode::NumPad6;
        map[VK_NUMPAD7] = Helios::KeyCode::NumPad7;
        map[VK_NUMPAD8] = Helios::KeyCode::NumPad8;
        map[VK_NUMPAD9] = Helios::KeyCode::NumPad9;

        map[VK_MULTIPLY] = Helios::KeyCode::NumPadMultiply;
        map[VK_ADD] = Helios::KeyCode::NumPadAdd;
        map[VK_SUBTRACT] = Helios::KeyCode::NumPadSubtract;
        map[VK_DECIMAL] = Helios::KeyCode::NumPadDecimal;
        map[VK_DIVIDE] = Helios::KeyCode::NumPadDivide;


        map[VK_APPS] = Helios::KeyCode::Menu;

        return map;
    }

    std::array<Helios::uint32, KeyCount> CreateVirtualKeyMap() {
        std::array<Helios::uint32, KeyCount> map{};
        map.fill(0);

        for (Helios::uint32 vk = 0; vk < MaxVirtualKeys; ++vk) {
            Helios::KeyCode key = CreateKeyMap()[vk];
            if (key != Helios::KeyCode::Unknown) {
                map[static_cast<size_t>(key)] = vk;
            }
        }
        return map;
    }

    const auto s_KeyMap = CreateKeyMap();
    const auto s_VirtualKeyMap = CreateVirtualKeyMap();
}

namespace Helios {
    KeyCode WindowsKeyMap::TranslateKey(uint32 virtualKey, uint64 lParam) {

        uint32 translatedVirtualKey = virtualKey;

        // This is to determine right and left shifts
        // The keyboard scan code is stored in bits 16-23 of lParam.
        // Shift it down to the lowest byte and mask out the remaining flags.
        uint32 scanCode = (lParam >> 16) & 0xFF;

        // Bit 24 of lParam are the extended bits required to determine the left and right alt and ctrl
        // 1ull because your lParam parameter is uint64. It avoids any possibility of integer promotion issues.
        bool isExtended = (lParam & (1ull << 24)) != 0;

        
        if (translatedVirtualKey == VK_SHIFT) {
            translatedVirtualKey = MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX);
        }
        else if (translatedVirtualKey == VK_CONTROL) {
            translatedVirtualKey = isExtended ? VK_RCONTROL : VK_LCONTROL;
        }
        else if (translatedVirtualKey == VK_MENU) {
            translatedVirtualKey = isExtended ? VK_RMENU : VK_LMENU;
        }
        if (translatedVirtualKey >= s_KeyMap.size()) {
            return KeyCode::Unknown;
        }
        return s_KeyMap[translatedVirtualKey];
    }

    uint32 WindowsKeyMap::ToVirtualKey(KeyCode keyCode) {
        size_t index = static_cast<size_t>(keyCode);
        if (index >= s_VirtualKeyMap.size()) {
            return 0;
        }
        return s_VirtualKeyMap[index];
    }
}