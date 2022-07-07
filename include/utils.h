#pragma once

#include "exceptions.h"

#include <array>
#include <optional>
#include <png.h>

namespace xxxDisplay
{

/**
 * @brief Compute a mod 97 checksum of a given numerical string. Only up to 9-digit inputs are supported at the moment.
 *
 * @param code A string containing only numerical characters of maximum length of 9 characters.
 * @return Computed checksum
 *
 * @throw exceptions::UnexpectedLength Received too long value, only up to 9-digits numbers are supported at the moment.
 * @throw exceptions::UnexpectedCharacter Received unsupported character in the input string. Only numeric
 * characters are supported.
 */
uint32_t getMod97(const std::string& code);

/**
 * Save a PNG image from provided 1-D pixel data. Created image will be 1-bit depth, greyscale and 1-bit high.
 * Each entry in the container will be cast to unsigned char, and so only first byte of data is significant.
 * Later bytes in the provided data will be ignored.
 *
 * The created image will have a width equal to eight times the size of the container minus value of ignore_bits
 * parameter. The ignore_bits parameter allow to generate images of any length. The value of ignore_bits should
 * be smaller than 8*data.size().
 *
 * @tparam Container a random access ordered data structure that holds a 1-byte of data per element
 * @param data 1-D container with pixel data
 * @param file_name name of the generated PNG image (with path). The parent directory must exists or
 * SaveFileException will be thrown.
 * @param ignored_bits number of bits to be ignored from the end of the stream. This value should be smaller than
 * 8*data.size().
 *
 * @throw SaveFileException Could not open the file for saving or and empty image has been requested.
 * @throw LibpngException Encounter an internal error from libpng.
 *
 */
template<typename Container>
void save1DPng(const Container& data, const std::string& file_name, size_t ignored_bits);

}

#include "utils.tpp"