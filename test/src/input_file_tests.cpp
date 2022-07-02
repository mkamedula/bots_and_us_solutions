#include "code_parser.h"
#include <catch2/catch.hpp>

SCENARIO("Received file is well-formatted file")
{
    GIVEN("A file with some codes")
    {
        botsAndUs::CodeParser parser("resources/valid_codes.txt");
        REQUIRE_NOTHROW(parser.exert());
    }
}

SCENARIO("Provided file may be ill-formatted")
{
    GIVEN("A file with one 3-digit code.")
    {
        botsAndUs::CodeParser parser("resources/too_short_code.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with one 5-digit code.")
    {
        botsAndUs::CodeParser parser("resources/too_long_code.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with a non-numerical first line.")
    {
        botsAndUs::CodeParser parser("resources/unexpected_input.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::WrongFileFormat);
    }

    GIVEN("A file with a non-numerical middle line.")
    {
        botsAndUs::CodeParser parser("resources/unexpected_input_2.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::WrongFileFormat);
    }

    GIVEN("A file with an unsupported character inside the code.")
    {
        botsAndUs::CodeParser parser("resources/unrecognised_character.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with an unsupported unicode character inside the code.")
    {
        botsAndUs::CodeParser parser("resources/unrecognised_character_unicode.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::UnexpectedCharacter);
    }

    GIVEN("A file encoded with a different standard (Expect UTF-8).")
    {
        botsAndUs::CodeParser parser("resources/ISO_encoding_codes.txt");
        REQUIRE_THROWS_AS(parser.exert(), botsAndUs::exceptions::WrongFileEncoding);
    }
}