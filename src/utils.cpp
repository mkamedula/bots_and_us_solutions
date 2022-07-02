#include "utils.h"

namespace botsAndUs
{

bool getBitCode(char id, std::array<bool,8>& code)
{

    const std::unordered_map<char, std::array<bool, 8>> bitMap{{'0', {0, 1, 1, 1, 0, 1, 1, 1}},
                                                               {'1', {0, 1, 0, 0, 0, 0, 1, 1}},
                                                               {'2', {1, 0, 1, 1, 0, 1, 1, 0}},
                                                               {'3', {1, 1, 0, 1, 0, 1, 1, 0}},
                                                               {'4', {1, 1, 0, 0, 0, 0, 1, 0}},
                                                               {'5', {1, 1, 0, 1, 0, 1, 0, 1}},
                                                               {'6', {1, 1, 1, 1, 0, 1, 0, 1}},
                                                               {'7', {0, 1, 0, 0, 0, 1, 1, 1}},
                                                               {'8', {1, 1, 1, 1, 0, 1, 1, 1}},
                                                               {'9', {1, 1, 0, 1, 0, 1, 1, 1}},

    };

    auto isCode = bitMap.find(id);

    if (isCode == bitMap.end())
    {
        return false;
    }

    code = isCode->second;

    return true;

}

}