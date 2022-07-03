#pragma once

#include <optional>
#include <png.h>
#include <array>
#include <deque>
#include <iostream>
#include <bitset>
#include "exceptions.h"

namespace botsAndUs
{
// TODO change it to std variant with error?
std::optional<uint32_t> getMod97(const std::string& code);

/**
 * based on (3/07/2022): http://www.libpng.org/pub/png/libpng-manual.txt and http://zarb.org/~gc/html/libpng.html
 * @param file_name
 */
void savePngImp(unsigned char& data, const std::string& file_name, size_t width);


    template<typename Container>
void savePng(Container& data, [[maybe_unused]] const std::string& file_name)
{
    unsigned char* c_data = (unsigned char*) malloc(sizeof(unsigned char) * data.size());

    for (size_t i = 0; i < data.size(); i++)
    {
        c_data[i] = static_cast<unsigned char>(data[i]);
    }

    savePngImp(*c_data, file_name, data.size());

    free(c_data);
}


}
