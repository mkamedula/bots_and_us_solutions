#pragma once

#include <unordered_map>

namespace xxxDisplay
{

/**
 * @brief This class provides operations directly related to the xxxDisplay hardware.
 *
 * High bit - inactive segment
 * Low bit - active segment
 */
class BitStream
{

  public:

    BitStream();

    /**
     * @brief Get current status of the display
     * @return current status of the display
     */
    const std::array<uint8_t, 32>& get();

    /**
     * @brief change status of the display
     * @param code 6-digit ASCII code to be displayed
     *
     * @throw exceptions::UnexpectedLength provided code of a wrong length, only 6-character
     * codes are supported at the moment
     * @throw exceptions::UnexpectedCharacter received unexpected character value. Only numerical values are supported.
     */
    void update(std::string_view code);

  protected:
    /**
     * Mapping between the supported ASCII characters and XXX display character segments
     */
    const std::unordered_map<char, int32_t> bitMap_{{'0', 0b01110111},
                                                    {'1', 0b01000010},
                                                    {'2', 0b10110110},
                                                    {'3', 0b11010110},
                                                    {'4', 0b11000011},
                                                    {'5', 0b11010101},
                                                    {'6', 0b11110101},
                                                    {'7', 0b01000110},
                                                    {'8', 0b11110111},
                                                    {'9', 0b11010111},};

    std::array<uint8_t, 32> pixelCode_ = {}; //! A full 256-bit code for a XXX display

    const size_t pixelOffsetBytes_ = 1; //! Offset to the first significant bit in bytes



};
}