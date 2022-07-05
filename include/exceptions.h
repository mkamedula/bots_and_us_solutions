#pragma once

#include <exception>
#include <string>

namespace xxxDisplay::exceptions
{


// TODO split the implementation, add comments
struct InputFileException : public std::exception
{
  private:
    std::string message = "An error processing input file.";

  public:
    InputFileException(const std::string& msg);

    InputFileException() = default;

    virtual ~InputFileException() = default;

    const char* what() const throw() override;
};

struct SaveFileException : public std::exception
{
  private:
    std::string message = "An error processing a file.";

  public:
    SaveFileException(const std::string& msg);

    SaveFileException() = default;

    virtual ~SaveFileException() = default;

    const char* what() const throw() override;
};


struct PngFileException : public std::exception
{
  private:
    std::string message = "An error processing a PNG image.";

  public:
    PngFileException(const std::string& msg);

    PngFileException() = default;

    virtual ~PngFileException() = default;

    const char* what() const throw() override;
};

struct FileDoesNotExists : public InputFileException
{
    FileDoesNotExists(const std::string& msg);

    FileDoesNotExists();

};


struct UnexpectedCodeLength : public InputFileException
{
    UnexpectedCodeLength(const std::string& msg);

    UnexpectedCodeLength()
        : InputFileException("A file contains at least one code that is of an unexpected length.")
    {
    };

};

struct UnexpectedCharacter : public InputFileException
{
    UnexpectedCharacter(const std::string& msg);

    UnexpectedCharacter();

};


} // namespace botsAndUs
