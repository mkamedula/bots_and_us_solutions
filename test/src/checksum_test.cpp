#include "utils.h"

#include <catch2/catch.hpp>

namespace xxxDisplay
{
SCENARIO("The checksum is being computed")
{
    GIVEN("3-digit number")
    {
        REQUIRE(getMod97("877") == 4);
    }

    GIVEN("4-digit number")
    {
        REQUIRE(getMod97("7331") == 56);
        REQUIRE(getMod97("9564") == 58);
    }
}

SCENARIO("An invalid string is provided to the checksum")
{
    GIVEN("A negative number")
    {
        REQUIRE_THROWS_AS(getMod97("-4586"), exceptions::UnexpectedCharacter);
    }

    GIVEN("A non-numerical string")
    {
        REQUIRE_THROWS_AS(getMod97("A text"), exceptions::UnexpectedCharacter);
    }

    GIVEN("A partial numeric string")
    {
        REQUIRE_THROWS_AS(getMod97("5f48"), exceptions::UnexpectedCharacter);
    }

    GIVEN("A long input with more than 32-bits")
    {
        REQUIRE_THROWS_AS(getMod97("77899458687"), exceptions::UnexpectedLength);
    }
}
}
