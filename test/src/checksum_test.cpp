#include "utils.h"

#include <catch2/catch.hpp>

namespace xxxDisplay
{
SCENARIO("The checksum is being computed")
{
    GIVEN("3-digit number")
    {
        REQUIRE(getMod97("877").value() == 4);
    }

    GIVEN("4-digit number")
    {
        REQUIRE(getMod97("7331").value() == 56);
        REQUIRE(getMod97("9564").value() == 58);
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

    GIVEN("A long input with more than 32-bits")
    {
        REQUIRE(getMod97("77899458687") == std::nullopt);
    }
}
}
