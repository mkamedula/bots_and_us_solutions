#include "exceptions.h"
#include "hardware.h"
#include "utils.h"

#include <algorithm>

namespace xxxDisplay
{

Hardware::Hardware()
{
    pixelCode_.fill(0b11111111);
}

const std::array<uint8_t, 32>& Hardware::get()
{
    return pixelCode_;
}

void Hardware::save(const std::string& file_name)
{
    save1DPng(get(), file_name, 0);
}


void Hardware::update(const std::string& code)
{
    if (code.size() != 6)
    {
        throw exceptions::UnexpectedLength("Bit stream received unexpected code length. Only six digit numbers are supported.");
    }

    if (std::any_of(code.begin(), code.end(), [&](const char c)
    {
        return !bitMap_.count(c);
    }))
    {
        throw exceptions::UnexpectedCharacter("Bit stream received unexpected character value. Only numerical values are supported.");
    }

    auto start = pixelOffsetBytes_;

    for (const auto& value: code)
    {
        pixelCode_[start++] = bitMap_.at(value);
    }
}


}