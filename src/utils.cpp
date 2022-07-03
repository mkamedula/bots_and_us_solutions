#include "utils.h"
#include "exceptions.h"
#include <boost/range/adaptor/reversed.hpp>

namespace botsAndUs
{
std::optional<uint32_t> getMod97(const std::string& code)
{

    if (std::any_of(code.begin(), code.end(), [](const auto& value)
    {
        return !std::isdigit(value);
    }))
    {
        return std::nullopt;
    }

    try
    {
        return std::stoi(code) % 97;
    }
    catch (std::out_of_range& e)
    {
        /** not implemented: support for string  over the 32-bit limit has not been implemented yet. */
        return std::nullopt;
    }
    catch (std::invalid_argument& e)
    {
        /** This should not happen, should it throw */
        return std::nullopt;
    }
}


}