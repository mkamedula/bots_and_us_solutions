#include "exceptions.h"
#include "led_screen.h"

#include <algorithm>

namespace botsAndUs
{

void LedScreen::update(std::string_view code)
{
    if (code.size() != 6)
    {
        throw exceptions::UnexpectedCodeLength();
    }

    if (std::any_of(code.begin(), code.end(), [&](const char c)
    {
        return !bitMap_.count(c);
    }))
    {
        throw exceptions::UnexpectedCharacter();
    }

    auto start = kPixelOffset;

    for (const auto& value: code)
    {
        pixelCode_[start++] = bitMap_.at(value);
    }
}

const std::array<uint8_t, 32>& LedScreen::get()
{
    return pixelCode_;
}

}