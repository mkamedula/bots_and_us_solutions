#include "led_screen.h"

namespace BotsAndUs
{

bool LedScreen::getBitCode_(char id, std::array<bool,8>& code) const
{

    auto isCode = bitMap_.find(id);

    if (isCode == bitMap_.end())
    {
        return false;
    }

    code = isCode->second;

    return true;

}

}