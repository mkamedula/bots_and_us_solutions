#include "exceptions.h"

#include <utility>

namespace xxxDisplay::exceptions
{

XxxDisplayException::XxxDisplayException(std::string msg): message(msg)
{

}

const char* XxxDisplayException::what() const noexcept
{
    return message.c_str();
}


InputFileException::InputFileException(std::string msg)
    : XxxDisplayException(std::move(msg))
{
}

SaveFileException::SaveFileException(std::string msg)
    : XxxDisplayException(std::move(msg))
{
}

LibpngException::LibpngException(std::string msg)
    : XxxDisplayException(std::move(msg))
{
}

UnexpectedLength::UnexpectedLength(std::string msg)
    : XxxDisplayException(std::move(msg))
{
}

UnexpectedCharacter::UnexpectedCharacter(std::string msg)
    : XxxDisplayException(std::move(msg))
{
}


}