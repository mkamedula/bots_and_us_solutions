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
 * @throw std::out_of_range Received too long value, only up to 9-digits is supported at the moment.
 * @throw std::invalid_argument Received unsupported character in the input string. Only numeric characters are supported.
 */
uint32_t getMod97(const std::string& code);

/**
 * @brief Save a 1-bit depth, greyscale PNG image from provided pixel data.
 * A generate image will have a size 1 by 8*data.size.
 *
 * Save a PNG image from provided pixel data. Created image will be 1-bit depth, greyscale and 1-bit high.
 * It will have a width equal to eight times the size of the container.
 *
 * @tparam Container a random access ordered data structure that holds a 1-byte of data per element
 * @param data pointer to the container with the pixel data
 * @param file_name name of the generated PNG image (with path)
 *
 * @throw SaveFileException Could not open the file for saving.
 * @throw LibpngException Encounter an internal error from libpng.
 */
template<typename Container>
void savePngRowImage(const Container& data, [[maybe_unused]] const std::string& file_name);

/**
 * @brief Save a 1-bit depth, greyscale PNG image from provided pixel data.
 *
 * @param data pointer to the container with the pixel data
 * @param file_name name of the generated PNG image (with path)
 * @param width a width of the image to be saved in pixels
 *
 * @throw SaveFileException Could not open the file for saving.
 * @throw LibpngException Encounter an internal error from libpng.
 */
void savePngImp(unsigned char& data, const std::string& file_name, size_t width);

}

#include "utils.tpp"