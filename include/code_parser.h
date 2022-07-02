#pragma once

#include "exceptions.h"

#include <fstream>
#include <string_view>


namespace botsAndUs
{
    class CodeParser
    {
      public:
        CodeParser(std::string_view file);

        void exert();

      private:
        std::ifstream input_;
    };
}
