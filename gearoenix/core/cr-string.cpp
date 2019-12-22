#include "cr-string.hpp"

bool gearoenix::core::String::is_character(const event::button::KeyboardKeyId ki) noexcept
{
    return to_character(ki).has_value();
}

std::optional<wchar_t> gearoenix::core::String::to_character(const event::button::KeyboardKeyId ki) noexcept
{
    switch (ki) {
    case event::button::KeyboardKeyId::Enter:
    case event::button::KeyboardKeyId::NumpadEnter:
        return '\n';
    case event::button::KeyboardKeyId::Tilda:
        return '`';
    case event::button::KeyboardKeyId::Less:
        return '<';
    case event::button::KeyboardKeyId::Greater:
        return '>';
    case event::button::KeyboardKeyId::Tab:
        return '\t';
    case event::button::KeyboardKeyId::Space:
        return ' ';
    case event::button::KeyboardKeyId::Minus:
    case event::button::KeyboardKeyId::NumpadMinus:
        return '-';
    case event::button::KeyboardKeyId::Equal:
        return '=';
    case event::button::KeyboardKeyId::LeftBracket:
        return '[';
    case event::button::KeyboardKeyId::RightBracket:
        return ']';
    case event::button::KeyboardKeyId::Semicolon:
        return ';';
    case event::button::KeyboardKeyId::Quote:
        return '\'';
    case event::button::KeyboardKeyId::Comma:
        return ',';
    case event::button::KeyboardKeyId::Dot:
    case event::button::KeyboardKeyId::NumpadDot:
        return '.';
    case event::button::KeyboardKeyId::Slash:
    case event::button::KeyboardKeyId::NumpadSlash:
        return '/';
    case event::button::KeyboardKeyId::Backslash:
        return '\\';
    case event::button::KeyboardKeyId::Num0:
    case event::button::KeyboardKeyId::Numpad0:
        return '0';
    case event::button::KeyboardKeyId::Num1:
    case event::button::KeyboardKeyId::Numpad1:
        return '1';
    case event::button::KeyboardKeyId::Num2:
    case event::button::KeyboardKeyId::Numpad2:
        return '2';
    case event::button::KeyboardKeyId::Num3:
    case event::button::KeyboardKeyId::Numpad3:
        return '3';
    case event::button::KeyboardKeyId::Num4:
    case event::button::KeyboardKeyId::Numpad4:
        return '4';
    case event::button::KeyboardKeyId::Num5:
    case event::button::KeyboardKeyId::Numpad5:
        return '5';
    case event::button::KeyboardKeyId::Num6:
    case event::button::KeyboardKeyId::Numpad6:
        return '6';
    case event::button::KeyboardKeyId::Num7:
    case event::button::KeyboardKeyId::Numpad7:
        return '7';
    case event::button::KeyboardKeyId::Num8:
    case event::button::KeyboardKeyId::Numpad8:
        return '8';
    case event::button::KeyboardKeyId::Num9:
    case event::button::KeyboardKeyId::Numpad9:
        return '9';
    case event::button::KeyboardKeyId::NumpadStar:
        return '*';
    case event::button::KeyboardKeyId::NumpadPlus:
        return '+';
    case event::button::KeyboardKeyId::A:
        return 'a';
    case event::button::KeyboardKeyId::B:
        return 'b';
    case event::button::KeyboardKeyId::C:
        return 'c';
    case event::button::KeyboardKeyId::D:
        return 'd';
    case event::button::KeyboardKeyId::E:
        return 'e';
    case event::button::KeyboardKeyId::F:
        return 'f';
    case event::button::KeyboardKeyId::G:
        return 'g';
    case event::button::KeyboardKeyId::H:
        return 'h';
    case event::button::KeyboardKeyId::I:
        return 'i';
    case event::button::KeyboardKeyId::J:
        return 'j';
    case event::button::KeyboardKeyId::K:
        return 'k';
    case event::button::KeyboardKeyId::L:
        return 'l';
    case event::button::KeyboardKeyId::M:
        return 'm';
    case event::button::KeyboardKeyId::N:
        return 'n';
    case event::button::KeyboardKeyId::O:
        return 'o';
    case event::button::KeyboardKeyId::P:
        return 'p';
    case event::button::KeyboardKeyId::Q:
        return 'q';
    case event::button::KeyboardKeyId::R:
        return 'r';
    case event::button::KeyboardKeyId::S:
        return 's';
    case event::button::KeyboardKeyId::T:
        return 't';
    case event::button::KeyboardKeyId::U:
        return 'u';
    case event::button::KeyboardKeyId::V:
        return 'v';
    case event::button::KeyboardKeyId::W:
        return 'w';
    case event::button::KeyboardKeyId::X:
        return 'x';
    case event::button::KeyboardKeyId::Y:
        return 'y';
    case event::button::KeyboardKeyId::Z:
        return 'z';
    default:
        return std::nullopt;
    }
}