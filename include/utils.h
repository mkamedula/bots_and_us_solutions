#pragma once

#include <array>
#include <optional>
#include <unordered_map>

namespace botsAndUs
{
    std::optional<uint32_t> getMod97(std::string_view code);

    [[nodiscard]] bool getBitCode(char id, std::array<bool,8>& code);

    [[nodiscard]] bool getPixelCode(std::string_view code, std::array<bool, 256>& pixelCode);

}
