#include "exceptions.h"

namespace xxxDisplay::exceptions
{

InputFileException::InputFileException(const std::string& msg)
    : message(msg)
{
}

const char* InputFileException::what() const throw()
{
    return message.c_str();
}

SaveFileException::SaveFileException(const std::string& msg)
    : message(msg)
{
}

const char* SaveFileException::what() const throw()
{
    return message.c_str();
}

PngFileException::PngFileException(const std::string& msg)
    : message(msg)
{
}

const char* PngFileException::what() const throw()
{
    return message.c_str();
}

FileDoesNotExists::FileDoesNotExists(const std::string& msg)
    : InputFileException(msg)
{
}

FileDoesNotExists::FileDoesNotExists()
    : InputFileException("Could not find a requested input file.")
{
}

UnexpectedCodeLength::UnexpectedCodeLength(const std::string& msg)
    : InputFileException(msg)
{
}

UnexpectedCharacter::UnexpectedCharacter(const std::string& msg)
    : InputFileException(msg)
{
}

UnexpectedCharacter::UnexpectedCharacter()
    : InputFileException("A file contains at least one code with a non-supported character in it.")
{
}
}