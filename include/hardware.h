#pragma once

#include <unordered_map>

namespace xxxDisplay
{

/**
 * This class provides operations directly related to the xxxDisplay hardware. It provides a translation from the
 * output of the business layer to the bit and pixel streams understandable by the hardware.
 * It holds a mapping between the higher-level human readable codes and internal hardware logic.
 *
 * High bit - inactive segment
 * Low bit - active segment
 */
class Hardware
{

  public:

    Hardware();

    /**
     * @brief Get current status of the display as a bit stream where active segments are represented by the low
     * bits and inactive segments are represented by the high bits.
     * @return current status of the display
     */
    const std::array<uint8_t, 32>& get();

    /**
     * @brief Update the bit stream of the display represented by this instance based on the human-readable string value.
     * @param code 6-digit ASCII code to be displayed containing only supported characters (see bitMap_)
     *
     * @throw exceptions::UnexpectedLength received a code of a wrong length, only 6-character codes are supported.
     * @throw exceptions::UnexpectedCharacter received unexpected character value. See bitMap_ filed for list
     * of supported characters.
     */
    void update(const std::string& code);

    /**
     * @brief Save current status of the display to the png file.
     * @param file_name name of the PNG file that will be created. The parent directory must exist or
     * a exceptions::SaveFileException will be throw and PNG images will not be created
     *
     * @throw LibpngException Encounter an internal error from a PNG library.
     * @throw SaveFileException Could not open the file for saving. Most likely the parent directory
     * does not exists or the application does not have sufficient privileges.
     *
     * @warning If the previous file with a given name exists in a destination directory it will be overwritten
     * by this method.
     */
    void save(const std::string& file_name);

  private:
    /**
     * Mapping between the supported ASCII characters and XXX display character segments
     */
    const std::unordered_map<char, uint8_t> bitMap_{{'0', 0b10001000},
                                                    {'1', 0b10111101},
                                                    {'2', 0b01001001},
                                                    {'3', 0b00101001},
                                                    {'4', 0b00111100},
                                                    {'5', 0b00101010},
                                                    {'6', 0b00001010},
                                                    {'7', 0b10111001},
                                                    {'8', 0b00001000},
                                                    {'9', 0b00101000},};

    std::array<uint8_t, 32> pixelCode_ = {}; //! A full 256-bit code for a XXX display

    const size_t pixelOffsetBytes_ = 1; //! Offset to the first significant bit in bytes



};
}