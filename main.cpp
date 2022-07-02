#include <array>
#include <unordered_map>
#include <iostream>


int main()
{
        const std::unordered_map<char, std::array<bool, 8>> bitMap{{'0', {0, 1, 1, 1, 0, 1, 1, 1}},
                                                         {'1', {0, 1, 0, 0, 0, 0, 1, 1}},
                                                         {'2', {1, 0, 1, 1, 0, 1, 1, 0}},
                                                         {'3', {1, 1, 0, 1, 0, 1, 1, 0}},
                                                         {'4', {1, 1, 0, 0, 0, 0, 1, 0}},
                                                         {'5', {1, 1, 0, 0, 0, 0, 1, 0}},
                                                         };

    return 0;
}
