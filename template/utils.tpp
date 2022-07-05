#pragma once

namespace xxxDisplay
{

/**
 * based on (3/07/2022): http://www.libpng.org/pub/png/libpng-manual.txt and http://zarb.org/~gc/html/libpng.html
 * @param file_name
 */
void savePngImp(unsigned char& data, const std::string& file_name, size_t width);

template<typename Container>
void savePngRowImage(const Container& data, const std::string& file_name)
{
    unsigned char* c_data = (unsigned char*) malloc(sizeof(unsigned char) * data.size());

    for (size_t i = 0; i < data.size(); i++)
    {
        //        auto test = std::bitset<8>(data[i]);
        //        for (size_t k = 0; k < test.size(); k++)
        //        {
        //
        //            c_data[test.size()*i+k] = test[test.size() - 1 - k] ? 0b11111111 : 0b00000000;
        //        }
        c_data[i] = static_cast<unsigned char>(data.at(i));
    }

    savePngImp(*c_data, file_name, data.size() * 8);

    free(c_data);
}

}