#include "business_logic.h"

#include <cxxopts.hpp>
#include <iomanip>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>


// Map all exception to the exit codes
enum ExitCodes
{
    SUCCESS = EXIT_SUCCESS,
    INPUT_FILE_ERROR = 1,
    LIBPNG_ERROR = 2,
    SAVE_FILE_ERROR = 3,
    SPDLOG_INIT_ERROR = 4,
    UNKNOWN_DESTINATION_POINT = 5,
    UNKNOWN_EXCEPTION = 6,
};

int main(int argc, char* argv[])
{
    std::shared_ptr<spdlog::logger> logger;
    try
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        logger = spdlog::basic_logger_mt("basic_logger", oss.str() + ".log");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        return ExitCodes::SPDLOG_INIT_ERROR;
    }

    logger->set_level(spdlog::level::info);
    logger->info("Start the Xxx Display Code Parser Application");

    // change log pattern
    logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");


    cxxopts::Options options("Serial manip com app");
    options.add_options()("f,file", "Name of the file to be processed including the path",
                          cxxopts::value<std::string>());
    options.add_options()("d,destination_folder", "directory where the output .png files will be loaded",
                          cxxopts::value<std::string>());
    options.add_options()("h,help", "Print usage");

    auto userInput = options.parse(argc, argv);


    if (userInput.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if (!userInput["file"].count())
    {
        logger->critical(
            "Please specify the input file, see --help for more details on the usage of the program.");
        return ExitCodes::INPUT_FILE_ERROR;
    }

    logger->info("Open file " + userInput["file"].as<std::string>());
    if (!userInput["destination_folder"].count())
    {
        logger->critical(
            "Please specify the destination folder, see --help for more details on the usage of the program.");
        return ExitCodes::UNKNOWN_DESTINATION_POINT;
    }

    logger->info("Files are saved to " + userInput["destination_folder"].as<std::string>());

    try
    {
        xxxDisplay::BusinessLogic parser(userInput["file"].as<std::string>(),
                                         userInput["destination_folder"].as<std::string>());
        parser.exert();
    }
    catch (xxxDisplay::exceptions::InputFileException& e)
    {
        logger->critical(e.what());
        return ExitCodes::INPUT_FILE_ERROR;
    }
    catch (xxxDisplay::exceptions::LibpngException& e)
    {
        logger->critical(e.what());
        return ExitCodes::LIBPNG_ERROR;
    }
    catch (xxxDisplay::exceptions::SaveFileException& e)
    {
        logger->critical(e.what());
        return ExitCodes::SAVE_FILE_ERROR;
    }
    catch (const std::exception& ex)
    {
        logger->critical("Program terminated due to unknown exception");
        return ExitCodes::UNKNOWN_EXCEPTION;
    }

    return ExitCodes::SUCCESS;
}
