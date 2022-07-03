#include "code_parser.h"
#include <cxxopts.hpp>

enum ExitCodes
{
    Success = EXIT_SUCCESS,
    InputFileError = 1,
    UnknownInputFile,
    UnknownDestinationPoint,
};

int main(int argc, char* argv[])
{
    cxxopts::Options options("Serial manip com app");
    options.add_options()("f,file", "Name of the file to be processed including the path", cxxopts::value<std::string>());
    options.add_options()("d,destination_folder", "directory where the output .png files will be loaded", cxxopts::value<std::string>());
    options.add_options()("h,help", "Print usage");

    auto userInput = options.parse(argc, argv);


    if (userInput.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // TODO consider adding logs
    if (!userInput["file"].count())
    {
        std::cout << "Please specify the input file, see --help for more details on the usage of the program." << std::endl;
        return ExitCodes::UnknownInputFile;
    }
    if (!userInput["destination_folder"].count())
    {
        std::cout << "Please specify the destination folder, see --help for more details on the usage of the program." << std::endl;
        return ExitCodes::UnknownDestinationPoint;
    }

    // TODO try to handle exceptions here
    botsAndUs::CodeParser parser(userInput["file"].as<std::string>(), userInput["destination_folder"].as<std::string>());
    parser.exert();

    return 0;
}
