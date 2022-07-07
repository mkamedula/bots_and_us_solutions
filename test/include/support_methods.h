#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <iostream>
#include <bitset>

namespace xxxDisplay::tests
{
/**
 * A helper struct to compare the PNG files
 */
struct PngData
{

    unsigned char bit_depth;
    uint32_t bytes;
    unsigned char color_type;
    uint32_t height;
    uint32_t width;

    std::vector<std::vector<unsigned char>> pixels;

    friend bool operator==(PngData const& l, PngData const& r) noexcept;
};

PngData readPngImage(const std::string& file_name);

void removePngFiles(const std::string& folder);

}