#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace xxxDisplay::tests
{
/**
 * A helper struct to compare the PNG files
 */
struct PngData
{

    unsigned char bit_depth;
    uint32_t bits_number;
    unsigned char color_type;
    uint32_t height;
    uint32_t width;

    std::vector <std::vector<unsigned char>> pixels;

    friend bool operator==(PngData const& l, PngData const& r) noexcept
    {
        return l.height == r.height && l.width == r.width && l.color_type == r.color_type &&
               l.bit_depth == r.bit_depth && l.pixels == r.pixels;
    }
};

PngData readPngImage(const std::string& file_name);

void removePngFiles(const std::string& folder);

}