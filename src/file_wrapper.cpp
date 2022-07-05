#include "file_wrapper.h"

#include "iostream"
#include "utils.h"

#include <algorithm>

namespace xxxDisplay
{

FileWrapper::FileWrapper(const std::string& file, const std::string& save_folder)
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
        throw exceptions::UnexpectedCodeLength();
    }

    std::reverse_copy(line_.begin(), line_.end(), reversed_line_.begin());

    auto checksum = getMod97(reversed_line_);

    if (!checksum.has_value())
    {
        throw exceptions::UnexpectedCharacter();
    }

    display_.update(std::to_string(checksum.value()) + line_);
    savePngRowImage(display_.get(), save_folder_ + "/" + line_ + ".png");
}

} // namespace botsAndUs