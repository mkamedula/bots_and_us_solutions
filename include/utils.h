#pragma once

#include "exceptions.h"

#include <array>
#include <optional>
#include <png.h>

namespace xxxDisplay
{

/**
 * @brief Compute a mod 97 checksum of a given numerical string
 * @param code a string containing only numerical characters of maximum length of 9 characters
 * @return computed checksum or a fail mode
 */
std::optional<uint32_t> getMod97(const std::string& code);

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
 */
template<typename Container>
void savePngRowImage(const Container& data, [[maybe_unused]] const std::string& file_name);

}

#include "utils.tpp"