#include "bit_stream.h"
#include <catch2/catch.hpp>
#include <iostream>


namespace xxxDisplay::tests
{

SCENARIO("A pixel code is correctly generated when a valid input code is provided.")
{

    GIVEN("A valid input code")
    {
        auto [code, solution] = GENERATE(table<std::string, std::array<uint8_t, 6>>(
            {
                std::make_tuple("561337",
                                std::array<uint8_t, 6>{
                                    0b00101010,
                                    0b00001010,
                                    0b10111101,
                                    0b00101001,
                                    0b00101001,
                                    0b10111001}),
                std::make_tuple("920834",
                                std::array<uint8_t, 6>{
                                    0b00101000,
                                    0b01001001,
                                    0b10001000,
                                    0b00001000,
                                    0b00101001,
                                    0b00111100})}));


        Hardware screen;

        THEN("The pixel code is generated correctly")
        {

            REQUIRE_NOTHROW(screen.update(code));

            REQUIRE(screen.get()[0] == 0b11111111);

            auto it = screen.get().begin() + 1;
            for (auto& pixel: solution)
            {
                REQUIRE(*it == pixel);
                it++;
            }

            REQUIRE(std::all_of(it, screen.get().end(), [](auto& value)
            {
                return value == 0b11111111;
            }));
        }
    }
}

SCENARIO("An invalid code has been provided to the pixel generator")
{
    Hardware screen;
    screen.update("920834");
    auto init_array = screen.get();

    GIVEN("An invalid input code")
    {
        auto data = GENERATE("67y895", "6", "asccd ty ", "88865556678", "o998i8");
        THEN("The method returns false and it does not affect the original input.")
        {
            REQUIRE_THROWS(screen.update(data));
            REQUIRE(screen.get() == init_array);
        }
    }
}
}