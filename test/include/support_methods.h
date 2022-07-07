#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace xxxDisplay::tests
{
/**
 * A helper struct to compare the PNG files
 */
struct PngData
{

    unsigned char bit_depth; //! Bit depth of the image
    uint32_t bytes; //! number of significant bytes in each row of the image
    unsigned char color_type; //! Color type of the image
    uint32_t height; //! height of the image in pixels
    uint32_t width; //! width of the image in pixels

    std::vector<std::vector<unsigned char>> pixels;

    friend bool operator==(PngData const& l, PngData const& r) noexcept;
};

/**
 * Read a PNG image from provided file
 *
 * @param file_name which image should be loaded
 * @return A struct describing the PNG image
 */
PngData readPngImage(const std::string& file_name);

/**
 * Remove PNG images from a given directory. This method is used to clean the directory after the tests has been
 * performed to avoid and residual files on the next test runs.
 *
 * @param directory A directory that should be cleaned.
 */
void removePngFiles(const std::string& directory);

/**
 * Print human readable comparison of discrepancies found between the PNG files. Only first difference found will
 * be reported.
 *
 * @param file_name_1 A files that is being compared
 * @param file_name_2 A files that file_name_1 is being compared to
 * @return
 */
std::string printComparison(const std::string& file_name_1, const std::string& file_name_2);

/**
 * A helper class to manage a temporary test directory. It is responsible for managing the life time of the
 * directory. It creates the resource on construction and removes it when the test is finished.
 */
class TestDirectory
{
  public:
    /**
     *
     * @param directory Path to the directory that is being managed by the class
     */
    explicit TestDirectory(const std::string& directory);

    ~TestDirectory();

  private:
    std::string directory_; //! Path to the directory that is being managed by the class
};

}