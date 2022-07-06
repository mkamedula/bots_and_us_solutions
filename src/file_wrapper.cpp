#include "file_wrapper.h"
#include "utils.h"

#include <algorithm>
#include <iomanip>
#include <utility>

namespace xxxDisplay
{

FileWrapper::FileWrapper(const std::string& file, std::string save_folder)
    : save_folder_(std::move(save_folder))
{
    input_.open(file);
    if (input_.fail())
    {
        throw exceptions::InputFileException("FileWrapper: Could not open the requested input file " + file + ".");
    }

    line_.resize(4);
    reversed_line_.resize(4);
}

void FileWrapper::exert()
{
    while (input_ >> line_)
    {
        processLine_();
    }
}

void FileWrapper::processLine_()
{
    if (line_.size() != 4)
    {
        throw exceptions::InputFileException(
            "FileWrapper: Received unexpected line length. Expected 4, received " + std::to_string(line_.size()) +
            ".");
    }

    std::reverse_copy(line_.begin(), line_.end(), reversed_line_.begin());

    try
    {
        auto checksum = getMod97(reversed_line_);
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << std::to_string(checksum);
        display_.update(ss.str() + line_);
    }
    catch (exceptions::UnexpectedLength& e)
    {
        throw exceptions::InputFileException(
            std::string("FileWrapper: ") + e.what());
    }
    catch (exceptions::UnexpectedCharacter& e)
    {
        throw exceptions::InputFileException(
            std::string("FileWrapper: ") + e.what());
    }

    savePngRowImage(display_.get(), save_folder_ + "/" + line_ + ".png");
}

} // namespace botsAndUs