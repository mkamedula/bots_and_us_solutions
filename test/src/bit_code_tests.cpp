#include "utils.h"

#include <catch2/catch.hpp>

namespace botsAndUs
{
SCENARIO("A valid input code digits are provided")
{
    GIVEN("A valid input code digit")
    {
        std::array<bool,8> test_array;

        REQUIRE(getBitCode('0',test_array));
        REQUIRE(test_array == std::array{false, true, true, true, false, true, true, true});

        REQUIRE(getBitCode('1',test_array));
        REQUIRE(test_array == std::array{false, true, false, false, false, false, true, false});

        REQUIRE(getBitCode('2', test_array));
        REQUIRE(test_array == std::array{true, false, true, true, false, true, true, false});

        REQUIRE(getBitCode('3', test_array));
        REQUIRE(test_array == std::array{true, true, false, true, false, true, true, false});

        REQUIRE(getBitCode('4', test_array));
        REQUIRE(test_array == std::array{true, true, false, false, false, false, true, true});

        REQUIRE(getBitCode('5', test_array));
        REQUIRE(test_array == std::array{true, true, false, true, false, true, false, true});

        REQUIRE(getBitCode('6', test_array));
        REQUIRE(test_array == std::array{true, true, true, true, false, true, false, true});

        REQUIRE(getBitCode('7', test_array));
        REQUIRE(test_array == std::array{false, true, false, false, false, true, true, false});

        REQUIRE(getBitCode('8', test_array));
        REQUIRE(test_array == std::array{true, true, true, true, false, true, true, true});

        REQUIRE(getBitCode('9', test_array));
        REQUIRE(test_array == std::array{true, true, false, true, false, true, true, true});
    }


    GIVEN("A invalid input code digit")
    {
        std::array<bool,8> init_array{true, false, false, true, true, false, true, false};
        std::array<bool,8> test_array = init_array;
        auto data = GENERATE('y', 'q', 'O');

        THEN("The method returns false and original input is not modified")
        {
            REQUIRE(getBitCode(data, test_array) == false);
            REQUIRE(test_array == init_array);
        }
    }
}
}