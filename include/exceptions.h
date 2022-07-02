#pragma once

#include "exception"

namespace botsAndUs::exceptions
{
struct InputFileExceptions : public std::exception
{
    const char* what() const throw()
    {
        return "An error processing input file.";
    }
};

struct UnexpectedCodeLength : public InputFileExceptions
{
    const char* what() const throw()
    {
        return "A file contains at least one code that is of an unexpected length.";
    }
};

struct UnexpectedCharacter : public InputFileExceptions
{
    const char* what() const throw()
    {
        return "A file contains at least one code with a non-supported character in it.";
    }
};

struct WrongFileFormat : public InputFileExceptions
{
    const char* what() const throw()
    {
        return "Received an ill-formatted file. At least one row is not a pure number.";
    }
};

struct WrongFileEncoding : public InputFileExceptions
{
    const char* what() const throw()
    {
        return "Received an file encoded with unexpected standard. Expected UTF-8 file.";
    }
};

} // namespace botsAndUs
