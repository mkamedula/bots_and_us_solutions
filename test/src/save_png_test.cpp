#include "utils.h"

#include <deque>

#include <catch2/catch.hpp>


namespace botsAndUs
{


[[nodiscard]] bool compareFiles(std::string_view file_name_1, std::string_view file_name_2);

SCENARIO("A valid stream of pixels is provided to the function")
{
    GIVEN("A valid pixel stream")
    {
        // TODO generate the reference PNG, test with arrays
        auto data = GENERATE(table < std::string, std::deque<bool>>)({
            std::make_tuple("test_1.png", std::deque<bool>{ 0, 1, 0, 0, 0, 1, 1, 0}),
            std::make_tuple("test_2.png", std::deque<bool>{ 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1})});

        THEN("A correct png file is being saved.")
        {
            REQUIRE(savePng(std::get<std::deque<bool>>(data.get()), "test.png"));
            REQUIRE(compareFiles("test.png", std::get<std::string>(data.get())));
            // TODO remove the test file (?)
        }
    }
}
}
