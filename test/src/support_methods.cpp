#include "exceptions.h"
#include "support_methods.h"

#include <bitset>
#include <cmath>
#include <filesystem>
#include <png.h>

namespace xxxDisplay::tests
{

PngData readPngImage(const std::string& file_name)
{
    /* open file and test for it being a png */
    FILE* fp = fopen(file_name.c_str(), "rb");
    if (!fp)
    {
        throw exceptions::InputFileException("File " + file_name + " could not be opened for reading.");
    }

    char header[8];    // 8 is the maximum size that can be checked
    [[maybe_unused]] auto t = fread(header, 1, 8, fp);

    /* initialize stuff */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        throw exceptions::LibpngException("png_create_read_struct failed");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
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

    PngData pngData;
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

    auto* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pngData.height);

    for (uint32_t y = 0; y < pngData.height; y++)
    {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    pngData.bytes = std::ceil(pngData.width * static_cast<double>(pngData.bit_depth) / 8.0);

    for (uint32_t y = 0; y < pngData.height; y++)
    {
        auto test = std::vector<unsigned char>{row_pointers[y], row_pointers[y] + pngData.bytes};
        pngData.pixels.push_back(test);
        free(row_pointers[y]);
    }

    free(row_pointers);
    fclose(fp);

    return pngData;
}

void removePngFiles(const std::string& directory)
{
    for (const auto & directoryIter : std::filesystem::directory_iterator(directory))
    {
        if (directoryIter.path().extension() == ".png")
        {
            std::filesystem::remove(directoryIter.path());
        }
    }
}

bool operator==(const PngData& l, const PngData& r) noexcept
{
    return l.height == r.height && l.width == r.width && l.color_type == r.color_type &&
        l.bit_depth == r.bit_depth && l.pixels == r.pixels;
}

std::string printComparison(const std::string& file_name_1, const std::string& file_name_2)
{
    auto data1 = readPngImage(file_name_1);
    auto data2 = readPngImage(file_name_2);

    if (data1.height != data2.height)
    {
        return "Height don't match: " + std::to_string(data1.height) + ", " + std::to_string(data2.height);
    }

    if (data1.width != data2.width)
    {
        return "Width don't match " + std::to_string(data1.width) + ", " + std::to_string(data2.width);
    }

    if (data1.bit_depth != data2.bit_depth)
    {
        return "Bit depth don't match " + std::to_string(data1.bit_depth) + ", " + std::to_string(data2.bit_depth);
    }

    for (uint32_t i = 0; i < data1.height; i++)
    {
        for (uint32_t k = 0; k < data1.bytes; k++)
        {
            if (data1.pixels[i][k] != data2.pixels[i][k])
            {
                return "pixel mismatch " + std::to_string(i) + ", " + std::to_string(k) + ": " + std::bitset<8>(data1.pixels[i][k]).to_string()
                       + "\t" + std::bitset<8>(data2.pixels[i][k]).to_string();
            }
        }
    }

    return "Both images match";
}

TestDirectory::TestDirectory(const std::string& directory)
    : directory_(directory)
{
    std::filesystem::create_directory(directory_);
}

TestDirectory::~TestDirectory()
{
    std::filesystem::remove_all(directory_);
}
}