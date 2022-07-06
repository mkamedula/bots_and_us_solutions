#include "support_methods.h"
#include "utils.h"

#include <catch2/catch.hpp>
#include <filesystem>
#include <string>

namespace xxxDisplay::tests
{

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
            REQUIRE_NOTHROW(savePngRowImage(pixels, "test.png"));
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
            REQUIRE_NOTHROW(savePngRowImage(pixels, "test.png"));
            REQUIRE(readPngImage("test.png") == readPngImage("../../test/resources/png_files/test_3-bit.png"));
            std::filesystem::remove("test.png");
        }
    }

}

}

