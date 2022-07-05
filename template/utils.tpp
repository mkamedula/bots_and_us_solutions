#pragma once

namespace xxxDisplay
{

template<typename Container>
void savePngRowImage(const Container& data, const std::string& file_name)
{
    auto* c_data = (unsigned char*) malloc(sizeof(unsigned char) * data.size());

    for (size_t i = 0; i < data.size(); i++)
    {
        c_data[i] = static_cast<unsigned char>(data.at(i));
    }

    savePngImp(*c_data, file_name, data.size() * 8);

    free(c_data);
}

}