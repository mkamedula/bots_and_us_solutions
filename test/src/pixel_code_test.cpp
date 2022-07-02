#include "utils.h"

#include <catch2/catch.hpp>


namespace botsAndUs
{
SCENARIO("A pixel code is correctly generated when a valid input code is provided.")
{
    // TODO TEMPLATE IT
    GIVEN("A valid input code")
    {
        std::array<bool, 256> test_array;

        auto data = GENERATE(table<std::string, std::array<bool, 48>>)({
            std::make_tuple( "561337", std::array<bool, 48>{1, 1, 0, 1, 0, 1, 0, 1,
                                                            1, 1, 1, 1, 0, 1, 0, 1,
                                                            0, 1, 0, 0, 0, 0, 1, 0,
                                                            1, 1, 0, 1, 0, 1, 1, 0,
                                                            1, 1, 0, 1, 0, 1, 1, 0,
                                                            0, 1, 0, 0, 0, 1, 1, 0}),
            std::make_tuple("920834", std::array<bool,48>{true, true, false, true, false, true, true, true,
                                                          true, false, true, true, false, true, true, false,
                                                          false, true, true, true, false, true, true, true,
                                                          true, true, true, true, false, true, true, true,
                                                          true, true, false, true, false, true, true, false,
                                                          true, true, false, false, false, false, true, true})
        });



        THEN("The pixel code is generated correctly")
        {
            //TODO make sure the data generator works
            REQUIRE(getPixelCode(std::get<std::string>(data.get()), test_array));
            //TODO make sure these are correct ranges
            REQUIRE(std::all_of(test_array.begin(), test_array.begin() + 8, [](auto& value)
            {
                return value == 0;
            }));

            auto it = test_array.begin() + 8;
            for (auto& pixel: std::get<std::array<bool, 48>>(data.get()))
            {
                REQUIRE(*it == pixel);
                it++;
            }

            REQUIRE(std::all_of(it, test_array.end(), [](auto& value)
            {
                return value == 0;
            }));
        }
    }
}

SCENARIO("An invalid code has been provided to the pixel generator")
{
    GIVEN("An invalid input code")
    {
        std::array<bool, 256> init_array;
        init_array[2] = 1;
        init_array[19] = 1;
        init_array[69] = 1;
        init_array[137] = 1;
        init_array[255] = 1;
        std::array<bool, 256> test_array = init_array;


        auto data = GENERATE("67y8956", "6", "asccd ty ", "88865556678");
        THEN("The method returns false and it does not affect the original input.")
        {
            REQUIRE(getPixelCode(data, test_array) == false);
            REQUIRE(test_array == init_array);
        }

    }
}
}