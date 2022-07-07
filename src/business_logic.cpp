#include "business_logic.h"
#include "utils.h"

#include <algorithm>
#include <iomanip>
#include <utility>

namespace xxxDisplay
{

BusinessLogic::BusinessLogic(const std::string& file, std::string save_directory)
    : save_directory_(std::move(save_directory))
{
    input_.open(file);
    if (input_.fail())
    {
        throw exceptions::InputFileException("BusinessLogic: Could not open the requested input file " + file + ".");
    }

    line_.resize(4);
    reversed_line_.resize(4);
}

void BusinessLogic::exert()
{
    while (input_ >> line_)
    {
        processLine_();
    }
}

void BusinessLogic::processLine_()
{
    if (line_.size() != 4)
    {
        throw exceptions::InputFileException(
            "BusinessLogic: Received unexpected line length. Expected 4, received " + std::to_string(line_.size()) +
            ".");
    }

    std::reverse_copy(line_.begin(), line_.end(), reversed_line_.begin());

    try
    {
        auto checksum = getMod97(reversed_line_);
        checksum_stream_.str("");
        checksum_stream_ << std::setw(2) << std::setfill('0') << std::to_string(checksum);
        display_.update(checksum_stream_.str() + line_);
    }
    catch (exceptions::UnexpectedLength& e)
    {
        throw exceptions::InputFileException(
            std::string("BusinessLogic: ") + e.what());
    }
    catch (exceptions::UnexpectedCharacter& e)
    {
        throw exceptions::InputFileException(
            std::string("BusinessLogic: ") + e.what());
    }

    display_.save(save_directory_ + "/" + line_ + ".png");
}

} // namespace botsAndUs