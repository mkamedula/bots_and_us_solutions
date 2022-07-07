#include "exceptions.h"
#include "hardware.h"
#include "utils.h"

#include <algorithm>
#include <iostream>

namespace xxxDisplay
{

Hardware::Hardware()
{
    pixelCode_.fill(0b11111111);
}

const std::array<uint8_t, 32>& Hardware::get() const
{
    return pixelCode_;
}

void Hardware::save(const std::string& file_name) const
{
    save1DPng_(get(), file_name);
}


void Hardware::update(const std::string& code)
{
    if (code.size() != 6)
    {
        throw exceptions::UnsupportedLength("Hardware received unexpected code length. Only six digit numbers are supported.");
    }

    if (std::any_of(code.begin(), code.end(), [&](const char c)
    {
        return !bitMap_.count(c);
    }))
    {
        throw exceptions::UnexpectedCharacter("Hardware received unexpected character value. Only numerical values are supported.");
    }

    auto start = pixelOffsetBytes_;

    for (const auto& value: code)
    {
        pixelCode_[start++] = bitMap_.at(value);
    }

}


void Hardware::save1DPng_(const std::array<uint8_t, 32>& data, const std::string& file_name) const
{
    /* create file */
    FILE* fp = fopen(file_name.c_str(), "wb");

    if (!fp)
    {
        throw exceptions::SaveFileException("File " + file_name + " could not be opened for writing.");
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

    png_set_IHDR(write_ptr, info_ptr, data.size()*8, 1, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        throw exceptions::LibpngException("Error during writing bytes");
    }

    png_byte* row_pointers[1];

    row_pointers[0] = (unsigned char*) malloc(data.size());

    for (size_t i = 0; i < data.size(); i++)
    {
        row_pointers[0][i] = static_cast<unsigned char>(data.at(i));
    }

    png_write_image(write_ptr, row_pointers);

    free(row_pointers[0]);

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