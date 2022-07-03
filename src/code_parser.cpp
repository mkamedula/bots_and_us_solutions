#include "code_parser.h"

#include "iostream"
#include "utils.h"

#include <algorithm>

namespace botsAndUs
{

CodeParser::CodeParser(const std::string& file, const std::string& save_folder)
    : save_folder_(save_folder)
{
    input_.open(file);
    if (input_.fail())
    {
        throw exceptions::FileDoesNotExists();
    }

    line_.reserve(4);
    reversed_line_.reserve(4);

}

void CodeParser::exert()
{
    while (input_ >> line_)
    {
        if (line_.size() != 4)
        {
            throw exceptions::UnexpectedCodeLength();
        }

        std::reverse_copy(line_.begin(), line_.end(), reversed_line_.begin());

        auto checksum = getMod97(reversed_line_);

        if (!checksum.has_value())
        {
            throw exceptions::UnexpectedCharacter();
        }

        screen_.update(std::to_string(checksum.value()) + line_);
    }
}

} // namespace botsAndUs