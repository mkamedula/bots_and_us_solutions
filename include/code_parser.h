#pragma once

#include "exceptions.h"
#include "led_screen.h"

#include <fstream>
#include <string_view>


namespace botsAndUs
{
    class CodeParser
    {
      public:
        CodeParser(const std::string& file, const std::string& save_folder);

        void exert();

      private:
        std::ifstream input_;
        std::string line_;
        std::string reversed_line_;
        botsAndUs::LedScreen screen_;
        std::string save_folder_;
    };
}
