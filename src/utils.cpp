#include "exceptions.h"
#include "utils.h"

#include <algorithm>

namespace xxxDisplay
{

uint32_t getMod97(const std::string& code)
{
    if (code.empty())
        return 0;

    if (std::any_of(code.begin(), code.end(), [](const auto& value)
    {
        return !std::isdigit(value);
    }))
    {
        throw exceptions::UnexpectedCharacter(
            "getMod97: Received unexpected character in a string. Only numerical values are supported at the moment.");
    }

    try
    {
        return std::stoi(code) % 97;
    }
    catch (std::out_of_range& e)
    {
        throw exceptions::UnexpectedLength("getMod97: Received too long input argument. "
                                           "Currently maximum 9-digit numbers are supported.");
    }

}


}