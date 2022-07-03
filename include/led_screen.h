#pragma once

#include <unordered_map>

namespace botsAndUs
{

class LedScreen
{

  public:

    LedScreen(){
        pixelCode_.fill(0b11111111);
    }
    void update(std::string_view code);

    const std::array<uint8_t, 32>& get();

  protected:
    std::array<uint8_t, 32> pixelCode_ = {};
    const size_t kPixelOffset = 1;

    const std::unordered_map<char, int32_t> bitMap_{{'0', 0b01110111},
                                                    {'1', 0b01000010},
                                                    {'2', 0b10110110},
                                                    {'3', 0b11010110},
                                                    {'4', 0b11000011},
                                                    {'5', 0b11010101},
                                                    {'6', 0b11110101},
                                                    {'7', 0b01000110},
                                                    {'8', 0b11110111},
                                                    {'9', 0b11010111},};

};
}