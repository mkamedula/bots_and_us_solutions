#include "utils.h"

#include <catch2/catch.hpp>

#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>

namespace xxxDisplay
{

/**
 * A helper struct to compare the PNG files
 */
struct PngData
{
    uint32_t height;
    uint32_t width;
    uint32_t bits_number;
    unsigned char color_type;
    unsigned char  bit_depth;

    std::vector<std::vector<unsigned char>> pixels;
//
    friend bool operator==(PngData const& l, PngData const& r) noexcept
    {
        return l.height == r.height && l.width == r.width && l.color_type == r.color_type &&
               l.bit_depth == r.bit_depth && l.pixels == r.pixels;
    }
};

PngData readPngImage(const std::string& file_name)
{
    uint32_t y;

    PngData pngData;

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep* row_pointers;

    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE* fp = fopen(file_name.c_str(), "rb");
    if (!fp)
    {
        throw exceptions::InputFileException("File " + file_name + " could not be opened for reading.");
    }

    [[maybe_unused]] auto t = fread(header, 1, 8, fp);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        throw exceptions::LibpngException("png_create_read_struct failed");
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        throw exceptions::LibpngException("png_create_info_struct failed");
    }


    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw exceptions::LibpngException("Error during init_io");
    }


    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    pngData.width = png_get_image_width(png_ptr, info_ptr);
    pngData.height = png_get_image_height(png_ptr, info_ptr);
    pngData.color_type = png_get_color_type(png_ptr, info_ptr);
    pngData.bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw exceptions::LibpngException("Error during read_image");
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pngData.height);
    for (y = 0; y < pngData.height; y++)
    {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    pngData.bits_number = std::ceil(pngData.width*static_cast<double>(pngData.bit_depth)/8.0);

    for (y = 0; y < pngData.height; y++)
    {
        auto test = std::vector<unsigned char>{row_pointers[y], row_pointers[y] + pngData.bits_number};
        pngData.pixels.push_back(test);
        free(row_pointers[y]);
    }

    free(row_pointers);
    fclose(fp);

    return pngData;
}

auto getSolution()
{
    std::array<uint8_t, 32> test;
    test.fill(0b11111111);
    std::array<uint8_t, 6> solution{0b00101010,
                                    0b00001010,
                                    0b10111101,
                                    0b00101001,
                                    0b00101001,
                                    0b10111001};

    for (size_t i = 0; i < solution.size(); i++)
    {
        test[1 + i] = solution[i];
    }

    return test;
}

// TODO add one more test file, test with non 4-digit case
SCENARIO("A valid stream of pixels is provided to the function")
{
    GIVEN("A valid pixel stream")
    {
        auto [file, stream] = GENERATE(table<std::string, std::array<uint8_t, 32>>({
            std::make_tuple("../../test/resources/png_files/1337_1bit.png", getSolution()), }));

        THEN("A correct png file is being saved.")
        {
            REQUIRE_NOTHROW(savePngRowImage(stream, "test.png"));
            REQUIRE(readPngImage("test.png") == readPngImage(file));
            // TODO remove the test file (?)
        }
    }
}

// TODO what are the file conditions here?

}
