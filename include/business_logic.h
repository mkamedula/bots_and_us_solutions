#pragma once

#include "exceptions.h"
#include "hardware.h"

#include <fstream>
#include <string>
#include <sstream>


namespace xxxDisplay
{
/**
 * This class provides an implementation of a business logic around the XXX Displays. It takes a
 * user provided file of desired codes and processes them to the desired display values including safety checks.
 * Then, for each generated code, it creates PNG images compatible with the XXX displays.
 *
 * The class expects an input text file with a set of 4-digit codes, one per line and no other characters.
 * For each code, it computes a mod 97 checksum, and appends it at the beginning of the code. Then it translates
 * the code to the PNG format that can be read by XXX display. The PNG files are saved to the directory provided to
 * the constructor.
 *
 * @warning The destination directory must exists, otherwise a exceptions::SaveFileException will be throw and no PNG
 * images will be created.
 * @warning This class may overwrite existing PNG images in the destination directory if the names collide.
 *
 */
class BusinessLogic
{
  public:
    /**
     *
     * @param file name of the file that contains the codes (including path to file)
     * @param save_directory where to save generated png files (including path to directory). The directory must already exist.
     *
     * @throw exceptions::InputFileException could not open the requested input file.
     */
    BusinessLogic(const std::string& file, std::string save_directory);

    /**
     * @brief Executed the PNG image generation routine for all codes.
     *
     * It loops over the whole file and generates the PNG images for each file.
     *
     * @throw exceptions::InputFileException encountered unexpected formatting in the input file
     * @throw exceptions::LibpngException encountered an error in the libpng library
     * @throw exceptions::SaveFileException could not open a file for saving. Most likely the parent directory
     * does not exists or it does not have sufficient privileges.
     */
    void exert();

  private:

    /**
     * @brief It processes last read code and generates the PNG image for it
     *
     * @throw exceptions::InputFileException encountered unexpected formatting in the input file
     * @throw exceptions::LibpngException encountered an error in the libpng library
     * @throw exceptions::SaveFileException could not open a file for saving. Most likely the parent directory
     * does not exists or it does not have sufficient privileges.
     */
    void processLine_();

    std::stringstream checksum_stream_; //! Auxiliary variable to fill the single digit checksum with leading zeros
    xxxDisplay::Hardware display_; //! Display abstraction that translates the input code to hardware bit stream and pixels
    std::ifstream input_; //! An input file
    std::string line_; //! Contents of the last line read
    std::string reversed_line_; //! Auxiliary variable to hold the reversed string for the checksum generation
    std::string save_directory_; //! directory where the generated png files are saved (including path to directory)

};
}
