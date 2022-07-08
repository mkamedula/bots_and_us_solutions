#include "utils.h"

#include <catch2/catch.hpp>

namespace xxxDisplay::tests
{
SCENARIO("The checksum is being requested for a valid input")
{
    GIVEN("1-digit number")
    {
        THEN("A checksum is computed correctly")
        {
            REQUIRE(getMod97("5") == 5);
        }
    }

    GIVEN("4-digit number")
    {
        THEN("A checksum is computed correctly")
        {
            REQUIRE(getMod97("7331") == 56);
        }
    }

    GIVEN("8-digit number")
    {
        THEN("A checksum is computed correctly")
        {
            REQUIRE(getMod97("12045678") == 24);
        }
    }

    GIVEN("A number with one digit checksum")
    {
        THEN("A checksum is computed correctly")
        {
            REQUIRE(getMod97("3591") == 2);
        }
    }

    GIVEN("A number with zero checksum")
    {
        THEN("A checksum is computed correctly")
        {
            REQUIRE(getMod97("1164") == 0);
        }
    }
}

SCENARIO("An invalid string is provided to the checksum")
{
    GIVEN("A negative number")
    {
        THEN("The checksum throws with the unexpected character exception")
        {
            REQUIRE_THROWS_AS(getMod97("-4586"), exceptions::UnexpectedCharacter);
        }
    }

    GIVEN("A non-numerical string")
    {
        THEN("The checksum throws with the unexpected character exception")
        {
            REQUIRE_THROWS_AS(getMod97("A text"), exceptions::UnexpectedCharacter);
        }
    }

    GIVEN("A partial numeric string")
    {
        THEN("The checksum throws with the unexpected character exception")
        {
            REQUIRE_THROWS_AS(getMod97("5f48"), exceptions::UnexpectedCharacter);
        }
    }

    GIVEN("A long input with more than 32-bits")
    {
        THEN("The checksum throws with an unsupported length exception")
        {
            REQUIRE_THROWS_AS(getMod97("77899458687"), exceptions::UnsupportedLength);
        }
    }
}
}
