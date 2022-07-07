#pragma once

#include <stdexcept>
#include <string>


namespace xxxDisplay::exceptions
{

/**
 * It is a generic base exception class for all expected exceptions thrown by the xxxDisplay namespace
 */
struct XxxDisplayException : public std::exception
{
  private:
    std::string message; //! A message describing an error

  public:
    /**
     * @param msg A message describing an error
     */
    explicit XxxDisplayException(std::string msg);

    ~XxxDisplayException() override = default;

    /**
     * @brief Provide a message describing the encountered issue
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
     * @param msg A message describing an error
     */
    explicit InputFileException(std::string msg);

    ~InputFileException() override = default;

};

/**
 * @brief An exception that is thrown when an error when opening/creating a file with write permission has
 * been encountered
 */
struct SaveFileException : public XxxDisplayException
{
  public:
    /**
    * @param msg A message describing an error
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
     * @param msg A message describing an error
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
     * @param msg A message describing an error
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
     * @param msg A message describing an error
     */
    explicit UnexpectedCharacter(std::string msg);

    ~UnexpectedCharacter() override = default;

};


} // namespace botsAndUs
