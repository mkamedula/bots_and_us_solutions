#include "utils.h"

#include <deque>

#include <catch2/catch.hpp>
#include <iostream>

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

namespace botsAndUs
{

// true the same, false different or does not exist
bool compareFiles(const std::string& file_name_1, const std::string& file_name_2)
{
    std::ifstream f1(file_name_1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(file_name_2, std::ifstream::binary | std::ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        std::cout << "One of the files could not be opened" << f1.fail() << ", " << f2.fail() << std::endl;

        return false; //file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        std::cout << "Size mismatch" << f1.tellg() << ", " << f2.tellg() << std::endl;
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);

    std::cout << "Compare contents" << std::endl;
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

auto getSolution()
{
    std::array<uint8_t, 32> test;
    test.fill(0b11111111);
    std::array<uint8_t, 6> solution{0b00101010,
                                    0b00001010,
                                    0b10111101,
                                    0b00101001,
                                    0b00101001,
                                    0b10111001};

    //    std::array<uint8_t, 6> solution{0b11010101,
//                                    0b11110101,
//                                    0b01000010,
//                                    0b11010110,
//                                    0b11010110,
//                                    0b01000110};

    for ( size_t i = 0; i < solution.size(); i++)
    {
        test[1 + i] = solution[i];
    }

    return test;
}

SCENARIO("A valid stream of pixels is provided to the function")
{
    GIVEN("A valid pixel stream")
    {
        //        // TODO generate the reference PNG, test with arrays
        //        auto [file, stream] = GENERATE(table < std::string, std::deque<bool>>({
        //            std::make_tuple("test_3.png", std::deque<bool>{ 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1 ,1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1}),
        //            std::make_tuple("test_1.png", std::deque<bool>{ 0, 1, 0, 0, 0, 1, 1, 0}),
        //            std::make_tuple("test_2.png", std::deque<bool>{ 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1}),
        //            }));

        // TODO generate the reference PNG, test with arrays

        auto [file, stream] = GENERATE(table<std::string, std::array<uint8_t, 32>>({
                                                                                     std::make_tuple(
                                                                                         "../../test/resources/png_files/1337.png", getSolution()),
                                                                                 }));

        THEN("A correct png file is being saved.")
        {
            std::cout << "new file" << std::endl;
            for (size_t i = 0; i < stream.size(); i++)
            {
                std::cout << i << ": " << std::bitset<8>(stream[i]) << std::endl;
            }
            std::cout << "end file" << std::endl;

            REQUIRE_NOTHROW(savePng(stream, "test.png"));
            REQUIRE(compareFiles("test.png", file));
            // TODO remove the test file (?)
        }
    }
}

}
