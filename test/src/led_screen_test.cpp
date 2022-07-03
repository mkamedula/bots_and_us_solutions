#include "led_screen.h"
#include <catch2/catch.hpp>
#include <iostream>


namespace botsAndUs
{

SCENARIO("A pixel code is correctly generated when a valid input code is provided.")
{
    // TODO TEMPLATE IT
    GIVEN("A valid input code")
    {
        auto [code, solution] = GENERATE( table<std::string, std::array<uint8_t, 6>>({
            std::make_tuple( "561337", std::array<uint8_t, 6>{0b11010101,
                                                            0b11110101,
                                                            0b01000010,
                                                            0b11010110,
                                                            0b11010110,
                                                            0b01000110}),
            std::make_tuple("920834", std::array<uint8_t, 6>{0b11010111,
                                                            0b10110110,
                                                            0b01110111,
                                                            0b11110111,
                                                            0b11010110,
                                                            0b11000011}) }));


        LedScreen screen;



        THEN("The pixel code is generated correctly")
        {

            REQUIRE_NOTHROW(screen.update(code));


            //TODO make sure these are correct ranges
            REQUIRE(screen.get()[0] == 0b11111111);

            auto it = screen.get().begin() + 1;
            for (auto& pixel: solution)
            {
                REQUIRE(*it == pixel); // TODO add message on fail?
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
    LedScreen screen;
    screen.update("920834");
    auto init_array = screen.get();

    GIVEN("An invalid input code")
    {
        auto data = GENERATE("67y8956", "6", "asccd ty ", "88865556678");
        THEN("The method returns false and it does not affect the original input.")
        {
            REQUIRE_THROWS(screen.update(data));
            REQUIRE(screen.get() == init_array); // TODO this should not work
        }

    }
}
}