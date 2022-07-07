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


}