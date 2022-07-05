#pragma once

#include "exceptions.h"
#include "bit_stream.h"

#include <fstream>
#include <string_view>


namespace xxxDisplay
{
/**
 * @brief This class generates the PNG images compatible with the XXX displays from an input text file.
 *
 * This class generates from an input text file PNG images compatible with the XXX displays. It expects an
 * input text file with a set of 4-digit codes, one per line. For each code, it computes a mod 97 checksum, and
 * appends it at the beginning of the code. Then it translates the code to the PNG format that can be read by
 * XXX display.
 *
 * @warning This class may overwrite existing PNG images in the destination folder if the names collide.
 *
 */
class FileWrapper
{
  public:
    /**
     *
     * @param file name of the file that contains the codes (including path to file)
     * @param save_folder where to save generated png files (including path to folder)
     */
    FileWrapper(const std::string& file, const std::string& save_folder);

    /**
     * @brief Executed the PNG image generation routine for all codes.
     *
     * It loops over the whole file and generates the PNG images for each file.
     */
    void exert();

  private:

    /**
     * @brief It processes last read code and generates the PNG image for it
     */
    void processLine_();

    std::ifstream input_; //! Hold stream of an input file
    std::string line_; //! Contents of the last read line
    std::string reversed_line_; //! Auxiliary string to hold the reversed string for the checksum generation
    xxxDisplay::BitStream display_; //! Generates a required bit stream for a given code
    std::string save_folder_; //! directory where the generated png files are saved (including path to folder)
};
}