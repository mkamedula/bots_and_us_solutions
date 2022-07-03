#include "utils.h"

#include <deque>

#include <catch2/catch.hpp>
#include <iostream>

#include <string>
#include <algorithm>

namespace botsAndUs
{

struct PngData
{
    uint32_t height;
    uint32_t width;
    unsigned char color_type;
    unsigned char  bit_depth;
    int  number_of_passes;
    unsigned char  interlace_type;
    unsigned char  compression_type;
    unsigned char  filter_type;
    std::vector<std::vector<unsigned char>> pixels;
//
    friend bool operator==(PngData const& l, PngData const& r) noexcept
    {
        return l.height == r.height && l.width == r.width && l.color_type == r.color_type &&
               l.bit_depth == r.bit_depth && l.number_of_passes == r.number_of_passes &&
               l.interlace_type == r.interlace_type && l.compression_type == r.compression_type &&
               l.filter_type == r.filter_type && l.pixels == r.pixels;
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
        std::cout << "[read_png_file] File %s could not be opened for reading" << std::endl;
    }

    [[maybe_unused]] auto t = fread(header, 1, 8, fp);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        std::cout << "[read_png_file] png_create_read_struct failed" << std::endl;
        return pngData;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        std::cout << "[read_png_file] png_create_info_struct failed" << std::endl;
        return pngData;
    }


    if (setjmp(png_jmpbuf(png_ptr)))
    {
        std::cout << "[read_png_file] Error during init_io" << std::endl;
        return pngData;
    }


    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    pngData.width = png_get_image_width(png_ptr, info_ptr);
    pngData.height = png_get_image_height(png_ptr, info_ptr);
    pngData.color_type = png_get_color_type(png_ptr, info_ptr);
    pngData.bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    pngData.number_of_passes = png_set_interlace_handling(png_ptr);
    pngData.interlace_type = png_get_interlace_type(png_ptr, info_ptr);
    pngData.compression_type = png_get_compression_type(png_ptr, info_ptr);
    pngData.filter_type = png_get_filter_type(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        std::cout << "[read_png_file] Error during read_image" << std::endl;
        return pngData;
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pngData.height);
    for (y = 0; y < pngData.height; y++)
    {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    for (y = 0; y < pngData.height; y++)
    {
        auto test = std::vector<unsigned char>{row_pointers[y], row_pointers[y] + pngData.width};
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

void printComparisson(const std::string& file_name_1, const std::string& file_name_2)
{
    auto data1 = readPngImage(file_name_1);
    auto data2 = readPngImage(file_name_2);

    if (data1.height != data2.height)
    {
        std::cout << "Height don't match " << data1.height << ", " << data2.height << std::endl;
    }

    if (data1.width != data2.width)
    {
        std::cout << "Width don't match " << data1.width << ", " << data2.width << std::endl;
    }

    for (uint32_t i = 0; i < data1.height; i++)
    {

        for (uint32_t k = 0; k < data1.width; k++)
        {

            if (data1.pixels[i][k] != data2.pixels[i][k])
            {
                std::cout << "pixel mismatch " << i << ", " << k << ": " << (data1.pixels[i][k] != data2.pixels[i][k] )<< std::endl;
            }
        }
    }

}

SCENARIO("A valid stream of pixels is provided to the function")
{
    GIVEN("A valid pixel stream")
    {
        auto [file, stream] = GENERATE(table<std::string, std::array<uint8_t, 32>>({
                                                                                       std::make_tuple(
                                                                                           "../../test/resources/png_files/1337.png",
                                                                                           getSolution()),
                                                                                   }));

        THEN("A correct png file is being saved.")
        {
            REQUIRE_NOTHROW(savePng(stream, "test.png"));
            printComparisson("test.png", file);
            REQUIRE(readPngImage("test.png") == readPngImage(file));
            // TODO remove the test file (?)
        }
    }
}

}
