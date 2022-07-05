#pragma once

#include <stdexcept>
#include <string>


namespace xxxDisplay::exceptions
{

/**
 * @brief It is a generic base exception class for all expected exceptions thrown by the xxxDisplay namespace
 */
struct XxxDisplayException : public std::exception
{
  private:
    std::string message; //! A message describing the exception

  public:
    /**
     * @param msg A message describing the exception
     */
    explicit XxxDisplayException(std::string msg);

    ~XxxDisplayException() override = default;

    /**
     * @brief Describe the encountered exception
     * @return A message describing the exception
     */
    [[nodiscard]] const char* what() const noexcept override;
};

/**
 * @brief An exception that is thrown when an error in an input file has been detected
 */
struct InputFileException : public XxxDisplayException
{

  public:
    /**
     * @param msg A message describing the exception
     */
    explicit InputFileException(std::string msg);

    ~InputFileException() override = default;

};

/**
 * @brief An exception that is thrown when an error in opening a file for saving has happened
 */
struct SaveFileException : public XxxDisplayException
{
  public:
    /**
     * @param msg A message describing the exception
     */
    explicit SaveFileException(std::string msg);

    ~SaveFileException() override = default;
};

/**
 * @brief An exception that is thrown when an error in a libpng library has been encountered
 */
struct LibpngException : public XxxDisplayException
{
  public:
    /**
     * @param msg A message describing the exception
     */
    explicit LibpngException(std::string msg);

    ~LibpngException() override = default;
};

/**
 * @brief An exception that is thrown when an method received an argument of an unexpected length
 */
struct UnexpectedLength : public XxxDisplayException
{
  public:
    /**
     * @param msg A message describing the exception
     */
    explicit UnexpectedLength(std::string msg);

    ~UnexpectedLength() override = default;

};

/**
 * @brief An exception that is thrown when an method received a string with an unexpected/unsupported character in it
 */
struct UnexpectedCharacter : public XxxDisplayException
{

  public:
    /**
     * @param msg A message describing the exception
     */
    explicit UnexpectedCharacter(std::string msg);

    ~UnexpectedCharacter() override = default;

};


} // namespace botsAndUs
