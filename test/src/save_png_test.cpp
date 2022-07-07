#include "support_methods.h"
#include "utils.h"

#include <catch2/catch.hpp>
#include <filesystem>
#include <string>
#include <bitset>

namespace xxxDisplay::tests
{
void printComparison(const std::string& file_name_1, const std::string& file_name_2)
{
    auto data1 = readPngImage(file_name_1);
    auto data2 = readPngImage(file_name_2);

    if (data1.height != data2.height)
    {
        std::cout << "Height don't match " << data1.height << ", " << data2.height << std::endl;
    }

    if (data1.width != data2.width)
    {
        std::cout << "Width don't match " << data1.width << ", " << data2.width << std::endl;
    }

    if (data1.bit_depth != data2.bit_depth)
    {
        std::cout << "Bit depth don't match " << data1.bit_depth << ", " << data2.bit_depth << std::endl;
    }

    for (uint32_t i = 0; i < data1.height; i++)
    {
        for (uint32_t k = 0; k < data1.bytes; k++)
        {
            if (data1.pixels[i][k] != data2.pixels[i][k])
            {
                std::cout << "pixel mismatch " << i << ", " << k << ": " << std::bitset<8>(data1.pixels[i][k]) << "\t" << std::bitset<8>(data2.pixels[i][k]) << std::endl;
            }
        }
    }

}

SCENARIO("A valid stream of pixels is provided to the function")
{
    GIVEN("A 256-bit pixel stream")
    {
        std::array<uint8_t, 32> pixels{};
        pixels.fill(0b11111111);
        std::array<uint8_t, 6> solution{0b00101010,
                                        0b00001010,
                                        0b10111101,
                                        0b00101001,
                                        0b00101001,
                                        0b10111001};

        for (size_t i = 0; i < solution.size(); i++)
        {
            pixels[1 + i] = solution[i];
        }

        THEN("A correct png file is being saved.")
        {
            REQUIRE_NOTHROW(save1DPng(pixels, "test.png", 0));
            REQUIRE(readPngImage("test.png") == readPngImage("../../test/resources/png_files/1337.png"));
            std::filesystem::remove("test.png");
        }
    }

    GIVEN("A 24-bit pixel stream")
    {
        std::vector<uint8_t> pixels{0b01101011,
                                    0b00111010,
                                    0b10100101,};

        THEN("A correct png file is being saved.")
        {
            REQUIRE_NOTHROW(save1DPng(pixels, "test.png", 0));
            REQUIRE(readPngImage("test.png") == readPngImage("../../test/resources/png_files/test_24-bit.png"));
            std::filesystem::remove("test.png");
        }
    }

    GIVEN("A 19-bit pixel stream")
    {
        std::vector<uint8_t> pixels{0b01101011,
                                    0b00111010,
                                    0b10100101,};

        THEN("A correct png file is being saved.")
        {
            REQUIRE_NOTHROW(save1DPng(pixels, "test.png", 5));
            printComparison("test.png", "../../test/resources/png_files/test_19-bit.png");
            REQUIRE(readPngImage("test.png") == readPngImage("../../test/resources/png_files/test_19-bit.png"));
            std::filesystem::remove("test.png");
        }
    }

}

SCENARIO("An empty PNG file is requested")
{

    GIVEN("An empty stream")
    {
        THEN("A file save exception is thrown.")
        {
            REQUIRE_THROWS_AS(save1DPng(std::vector<uint8_t>{}, "test.png", 0), exceptions::SaveFileException);
        }
    }

    GIVEN("A 24-bit pixel stream with all bits ignored")
    {
        THEN("A file save exception is thrown.")
        {
            std::vector<uint8_t> pixels{0b01101011,
                                        0b00111010,
                                        0b10100101,};
            REQUIRE_THROWS_AS(save1DPng(pixels, "test.png", 24), exceptions::SaveFileException);
        }
    }
}
}

