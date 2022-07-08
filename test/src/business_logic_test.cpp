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
        WHEN("The class is constructed")
        {
            THEN("The class throws an input file exception")
            {
                REQUIRE_THROWS_AS(BusinessLogic("not_here.txt", "."), exceptions::InputFileException);
            }
        }
    }
}

SCENARIO("Received file is well-formatted")
{
    GIVEN("A valid file with codes")
    {
        BusinessLogic parser("../../test/resources/input_files/valid_codes.txt", ".");

        WHEN("The parser executes")
        {
            THEN("The parser executes successfully")
            {
                REQUIRE_NOTHROW(parser.exert());
            }

            std::string test_id = GENERATE("2553.png", "0129.png", "3140.png", "6718.png", "1953.png", "4611.png");

            AND_THEN("The correct PNG files are generated")
            {
                INFO(printComparison(test_id, "../../test/resources/png_files/" + test_id));
                REQUIRE(readPngImage(test_id) == readPngImage("../../test/resources/png_files/" + test_id));
                std::filesystem::remove(test_id);
            }
        }
    }

}

SCENARIO("Provided file may be ill-formatted")
{
    GIVEN("A file with one 3-digit code.")
    {
        BusinessLogic parser("../../test/resources/input_files/too_short_code.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }
        removePngFiles(".");
    }

    GIVEN("A file with one 5-digit code.")
    {
        BusinessLogic parser("../../test/resources/input_files/too_long_code.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }
        removePngFiles(".");
    }

    GIVEN("A file with a non-numerical first line.")
    {
        BusinessLogic parser("../../test/resources/input_files/unexpected_input.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }
        removePngFiles(".");
    }

    GIVEN("A file with a non-numerical middle line.")
    {
        BusinessLogic parser("../../test/resources/input_files/unexpected_input_2.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }
        removePngFiles(".");
    }

    GIVEN("A file with an unsupported character inside the code.")
    {
        BusinessLogic parser("../../test/resources/input_files/unrecognised_character.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }

        removePngFiles(".");
    }

    GIVEN("A file with an unsupported unicode character inside the code.")
    {
        BusinessLogic parser("../../test/resources/input_files/unrecognised_character_unicode.txt", ".");
        WHEN("The parser executes")
        {
            THEN("An error is detected")
            {
                REQUIRE_THROWS_AS(parser.exert(), exceptions::InputFileException);
            }
        }
        removePngFiles(".");
    }
}


SCENARIO("Files are saved to a desired directory")
{
    GIVEN("A valid file with codes and a destination directory")
    {
        std::string directory = "test_directory_2";

        TestDirectory manageDirectory(directory);

        BusinessLogic parser("../../test/resources/input_files/6718_code.txt", directory);

        std::string test_id = "6718.png";

        WHEN("The parser executes successfully")
        {
            REQUIRE_NOTHROW(parser.exert());
            THEN("The PNG files are saved to a desired directory")
            {
                REQUIRE(readPngImage(directory + "/" + test_id) ==
                        readPngImage("../../test/resources/png_files/" + test_id));
            }
        }


    }
}

SCENARIO("The destination directory does not exists")
{
    GIVEN("A wrong destination directory")
    {
        BusinessLogic parser("../../test/resources/input_files/valid_codes.txt", "./not_here");
        THEN("Class throws a save file exception")
        {
            REQUIRE_THROWS_AS(parser.exert(), exceptions::SaveFileException);
        }
    }
}

}