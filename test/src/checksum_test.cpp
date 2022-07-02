#include "utils.h"

#include <catch2/catch.hpp>

namespace botsAndUs
{
SCENARIO("The checksum is being computed")
{
    GIVEN("3-digit number")
    {
        REQUIRE(getMod97("778") == 4);
    }

    GIVEN("4-digit number")
    {
        REQUIRE(getMod97("1337") == 56);
        REQUIRE(getMod97("4659") == 40);
    }

    GIVEN("A long input with more than 32-bits")
    {
        REQUIRE(getMod97("77899458687") == 37);
    }
}

SCENARIO("An invalid string is provided to the checksum")
{
    GIVEN("A negative number")
    {
        REQUIRE(getMod97("-4586") == std::nullopt);
    }

    GIVEN("A non-numerical string")
    {
        REQUIRE(getMod97("A text") == std::nullopt);
    }

    GIVEN("A partial numeric string")
    {
        REQUIRE(getMod97("5f48") == std::nullopt);
    }
}
}
