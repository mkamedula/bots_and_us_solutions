#include "file_wrapper.h"
#include <catch2/catch.hpp>

namespace xxxDisplay
{

//TODO test full excert, or add next(), test next then excert?

SCENARIO("Provided input file does not exists")
{
    GIVEN("A non-existing file path")
    {
        REQUIRE_THROWS_AS(FileWrapper("not_here.txt", "."), exceptions::FileDoesNotExists);
    }
}

SCENARIO("Received file is well-formatted file")
{
    GIVEN("A file with some codes")
    {
        FileWrapper parser("../../test/resources/input_files/valid_codes.txt", ".");
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
        FileWrapper parser("../../test/resources/input_files/too_short_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with one 5-digit code.")
    {
        FileWrapper parser("../../test/resources/input_files/too_long_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCodeLength);
    }

    GIVEN("A file with a non-numerical first line.")
    {
        FileWrapper parser("../../test/resources/input_files/unexpected_input.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with a non-numerical middle line.")
    {
        FileWrapper parser("../../test/resources/input_files/unexpected_input_2.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with an unsupported character inside the code.")
    {
        FileWrapper parser("../../test/resources/input_files/unrecognised_character.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::UnexpectedCharacter);
    }

    GIVEN("A file with an unsupported unicode character inside the code.")
    {
        FileWrapper parser("../../test/resources/input_files/unrecognised_character_unicode.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
    }
}
}