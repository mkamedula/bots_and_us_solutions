#pragma once

#include <string>
#include "exception"

namespace botsAndUs::exceptions
{

struct InputException : public std::exception
{
  private:
    std::string message = "An error processing input file.";

  public:
    InputException(const std::string& msg)
        : message(msg)
    {
    }

    InputException() = default;

    virtual ~InputException() = default;

    const char* what() const throw() override
    {
        return message.c_str();
    }
};

struct FileException : public std::exception
{
  private:
    std::string message = "An error processing a file.";

  public:
    FileException(const std::string& msg)
        : message(msg)
    {
    }

    FileException() = default;

    virtual ~FileException() = default;

    const char* what() const throw() override
    {
        return message.c_str();
    }
};


struct PngException : public std::exception
{
  private:
    std::string message = "An error processing a PNG image.";

  public:
    PngException(const std::string& msg)
        : message(msg)
    {
    }

    PngException() = default;

    virtual ~PngException() = default;

    const char* what() const throw() override
    {
        return message.c_str();
    }
};

struct FileDoesNotExists : public InputException
{
    FileDoesNotExists(const std::string& msg)
        : InputException(msg)
    {
    }

    FileDoesNotExists()
        : InputException("Could not find a requested input file.")
    {
    };

};


struct UnexpectedCodeLength : public InputException
{
    UnexpectedCodeLength(const std::string& msg)
        : InputException(msg)
    {
    }

    UnexpectedCodeLength()
        : InputException("A file contains at least one code that is of an unexpected length.")
    {
    };

};

struct UnexpectedCharacter : public InputException
{
    UnexpectedCharacter(const std::string& msg)
        : InputException(msg)
    {
    }

    UnexpectedCharacter()
        : InputException("A file contains at least one code with a non-supported character in it.")
    {
    };

};


} // namespace botsAndUs
