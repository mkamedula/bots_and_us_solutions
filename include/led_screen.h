#pragma once

#include <array>
#include <unordered_map>

namespace BotsAndUs
{

class LedScreen
{

  public:

    [[nodiscard]] bool update(std::string_view code);

    const std::array<bool, 256>& get();

    bool save(std::string_view folder);

  protected:
    [[nodiscard]] bool getBitCode_(char id, std::array<bool,8>& code) const;

    std::array<bool, 256> pixelCode_;

    const std::unordered_map<char, std::array<bool, 8>> bitMap_{{'0', {0, 1, 1, 1, 0, 1, 1, 1}},
                                                               {'1', {0, 1, 0, 0, 0, 0, 1, 1}},
                                                               {'2', {1, 0, 1, 1, 0, 1, 1, 0}},
                                                               {'3', {1, 1, 0, 1, 0, 1, 1, 0}},
                                                               {'4', {1, 1, 0, 0, 0, 0, 1, 0}},
                                                               {'5', {1, 1, 0, 1, 0, 1, 0, 1}},
                                                               {'6', {1, 1, 1, 1, 0, 1, 0, 1}},
                                                               {'7', {0, 1, 0, 0, 0, 1, 1, 1}},
                                                               {'8', {1, 1, 1, 1, 0, 1, 1, 1}},
                                                               {'9', {1, 1, 0, 1, 0, 1, 1, 1}}, };

};
}