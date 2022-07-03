#pragma once

#include <optional>
#include <png.h>

namespace botsAndUs
{
    std::optional<uint32_t> getMod97(std::string_view code);

    template<typename Container>
    [[nodiscard]] bool savePng(const Container& data, std::string_view file_name);


}
