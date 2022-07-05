#include "exceptions.h"
#include "bit_stream.h"

#include <algorithm>

namespace xxxDisplay
{

void BitStream::update(std::string_view code)
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

    auto start = pixelOffsetBytes_;

    for (const auto& value: code)
    {
        pixelCode_[start++] = bitMap_.at(value);
    }
}

const std::array<uint8_t, 32>& BitStream::get()
{
    return pixelCode_;
}

BitStream::BitStream()
{
    pixelCode_.fill(0b11111111);
}

}