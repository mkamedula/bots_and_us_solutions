#include "exceptions.h"
#include "utils.h"

#include <algorithm>

namespace xxxDisplay
{

uint32_t getMod97(const std::string& code)
{
    if (code.empty())
        return 0;

    if (std::any_of(code.begin(), code.end(), [](const auto& value)
    {
        return !std::isdigit(value);
    }))
    {
        throw exceptions::UnexpectedCharacter(
            "getMod97: Received unexpected character in a string. Only numerical values are supported at the moment.");
    }

    try
    {
        return std::stoi(code) % 97;
    }
    catch (std::out_of_range& e)
    {
        throw exceptions::UnexpectedLength("getMod97: Received too long input argument. "
                                           "Currently maximum 9-digit numbers are supported.");
    }

}


void savePngImp(unsigned char& data, const std::string& file_name, [[maybe_unused]] size_t width)
{
    /* create file */
    FILE* fp = fopen(file_name.c_str(), "wb");

    if (!fp)
    {
        throw exceptions::SaveFileException("File " + file_name + " could not be opened for writing");
    }

    png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!write_ptr)
    {
        throw exceptions::LibpngException("png_create_write_struct failed");
    }

    png_infop info_ptr = png_create_info_struct(write_ptr);
    if (!info_ptr)
    {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        throw exceptions::LibpngException("png_create_info_struct failed");
    }

    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, &info_ptr);
        fclose(fp);
        throw exceptions::LibpngException("Error during init_io");
    }

    png_init_io(write_ptr, fp);

    png_set_filter(write_ptr, 0, PNG_FILTER_NONE);

    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        throw exceptions::LibpngException("Error during writing header");
    }

    png_set_IHDR(write_ptr, info_ptr, width, 1, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        throw exceptions::LibpngException("Error during writing bytes");
    }

    png_byte* row_pointers[1];

    row_pointers[0] = &data;

    png_write_image(write_ptr, row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        throw exceptions::LibpngException("Error during end of write");
    }

    png_write_end(write_ptr, NULL);

    png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
    fclose(fp);
}

}