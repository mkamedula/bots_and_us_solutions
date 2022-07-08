#include "exceptions.h"
#include "xxx_display.h"
#include "support_methods.h"

#include <catch2/catch.hpp>

namespace xxxDisplay::tests
{

SCENARIO("A pixel code is correctly generated when a valid input code is provided.")
{

    GIVEN("A valid input code and a display object")
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

        XxxDisplay screen;

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


            GIVEN("A valid directory")
            {
                std::string directory = "test_directory";

                TestDirectory manageDirectory(directory);

                WHEN("The XXX display is asked to save an image")
                {
                    REQUIRE_NOTHROW(screen.save(directory + "/" + code + ".png"));
                    THEN("The correct PNG image is saved in the desired directory")
                    {
                        INFO(printComparison(directory + std::string("/") + code + ".png",
                                             "../../test/resources/png_files/" + code + ".png"));
                        REQUIRE(readPngImage(directory + std::string("/") + code + ".png") ==
                                readPngImage("../../test/resources/png_files/" + code + ".png"));
                    }
                }
            }

            GIVEN("An in-valid directory")
            {
                std::string directory = "not_here";
                WHEN("The XXX display is asked to save an image")
                {
                    THEN("A save file exception is thrown")
                    {
                        REQUIRE_THROWS_AS(screen.save(directory + "/" + code + ".png"),
                                          exceptions::SaveFileException);
                    }
                }
            }
        }
    }
}

SCENARIO("An invalid code has been provided to the pixel generator")
{
    GIVEN("A display object with a valid state")
    {
        XxxDisplay screen;
        screen.update("920834");
        auto init_array = screen.get();

        WHEN("An invalid input code is send to the display")
        {
            auto data = GENERATE("67y895", "6", "asccd ty ", "88865556678", " 998i8");
            THEN("The method returns false and the display state is not affected.")
            {
                REQUIRE_THROWS(screen.update(data));
                REQUIRE(screen.get() == init_array);
            }
        }
    }
}
}