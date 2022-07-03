#include "code_parser.h"
#include <catch2/catch.hpp>

namespace botsAndUs
{


SCENARIO("Provided input file does not exists")
{
    GIVEN("A non-existing file path")
    {
        REQUIRE_THROWS_AS(CodeParser("not_here.txt", "."), exceptions::FileDoesNotExists);
    }
}

SCENARIO("Received file is well-formatted file")
{
    GIVEN("A file with some codes")
    {
        CodeParser parser("../../test/resources/input_files/valid_codes.txt", ".");
        THEN("The parser exits successfully")
        {
            REQUIRE_NOTHROW(parser.exert());
        }
    }
}

SCENARIO("Provided file may be ill-formatted")
{
    GIVEN("A file with one 3-digit code.")
    {
        CodeParser parser("../../test/resources/input_files/too_short_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with one 5-digit code.")
    {
        CodeParser parser("../../test/resources/input_files/too_long_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with a non-numerical first line.")
    {
        CodeParser parser("../../test/resources/input_files/unexpected_input.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with a non-numerical middle line.")
    {
        CodeParser parser("../../test/resources/input_files/unexpected_input_2.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with an unsupported character inside the code.")
    {
        CodeParser parser("../../test/resources/input_files/unrecognised_character.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with an unsupported unicode character inside the code.")
    {
        CodeParser parser("../../test/resources/input_files/unrecognised_character_unicode.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputException);
    }
}
}