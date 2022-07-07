#include "business_logic.h"
#include "support_methods.h"

#include <catch2/catch.hpp>
#include <filesystem>

namespace xxxDisplay::tests
{

SCENARIO("Requested input file does not exists")
{
    GIVEN("A non-existing file path")
    {
        REQUIRE_THROWS_AS(BusinessLogic("not_here.txt", "."), exceptions::InputFileException);
    }
}

SCENARIO("Received file is well-formatted")
{
    GIVEN("A valid file with codes and a destination folder")
    {
        std::filesystem::create_directory("test_folder");

        auto folder = GENERATE(".", "test_folder");

        BusinessLogic parser("../../test/resources/input_files/valid_codes.txt", folder);

        THEN("The parser exits successfully")
        {
            REQUIRE_NOTHROW(parser.exert());
        }

        std::string test_id = GENERATE("2553.png", "0129.png", "3140.png", "6718.png", "1953.png", "4611.png");

        THEN("The correct PNG files are generated")
        {
            REQUIRE(readPngImage(folder + std::string("/") + test_id) == readPngImage("../../test/resources/png_files/" + test_id));
            std::filesystem::remove(folder + std::string("/") + test_id);
        }


    }
}

SCENARIO("Provided file may be ill-formatted")
{
    GIVEN("A file with one 3-digit code.")
    {
        BusinessLogic parser("../../test/resources/input_files/too_short_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }

    GIVEN("A file with one 5-digit code.")
    {
        BusinessLogic parser("../../test/resources/input_files/too_long_code.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }

    GIVEN("A file with a non-numerical first line.")
    {
        BusinessLogic parser("../../test/resources/input_files/unexpected_input.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }

    GIVEN("A file with a non-numerical middle line.")
    {
        BusinessLogic parser("../../test/resources/input_files/unexpected_input_2.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }

    GIVEN("A file with an unsupported character inside the code.")
    {
        BusinessLogic parser("../../test/resources/input_files/unrecognised_character.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }

    GIVEN("A file with an unsupported unicode character inside the code.")
    {
        BusinessLogic parser("../../test/resources/input_files/unrecognised_character_unicode.txt", ".");
        REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
        removePngFiles(".");
    }
}

}