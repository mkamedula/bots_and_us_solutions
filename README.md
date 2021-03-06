# Code Parser for XXX Display 

This repository contains software to process an input file of 4-digit codes to PNG images understandable by XXX Displays.

Input files are expected to be pure text files, where each line consists of a 4-digit number (a code), and no other character is present in the text file.

For each code, a 97 mod checksum is prepended to the number. It results in a 6-digit code. For each 6-digit number, a PNG image is generated. This PNG image can be sent to the XXX Display to display the generated code. Each file is named based on the 4-digit initial code, e.g. a code '8420' will result in an output file '8420.png'. All files are saved to the directory specified as an input argument to the program.


# INSTALL

## Tested set-up - Minimum requirements

* CMake 3.21 - requires support for CMakePresets
* gcc 10.3 - at least compatible with C++17 standard
* libpng 1.6.37
* Ubuntu 20.04.4 LTS

## Installation procedure:

To install the program - minimum CMake 3.21, gcc 10:

* make sure the libpng is installed on the systems
  * sudo apt-get install libpng-dev
* check CMake version, minimum CMake 3.21
  * cmake --version 
* check gcc version, minimum gcc 10
  * gcc --version 
* download this repository
  * git clone https://github.com/mkamedula/bots_and_us_solutions
* go to the install_script directory inside the git repo directory
* add executable permissions to the installation script.
  * chmod +x ./install.sh
* run the installation script. Please be aware that at least CMake 3.21 is required for the script to execute correctly. The script will install all third-party libraries that are not mentioned in the minimum requirements section (see Third party libraries section), and the code itself
  * ./install.sh
* By default, the script will install the files to the ${GIT_ROOT_DIR}/install directory, where GIT_ROOT_DIR is a root directory of this repository. If you want to change the installation directory, you can do it using the input arguments
  * ./install.sh {CLEAN} {INSTALL_DIRECTORY} {CMAKE_BUILD_TYPE} {CMAKE}, 
  * where CLEAN takes true/false values and defines whether the clean build should be performed, CMAKE_BUILD_TYPE is a build type used and a preset to be loaded, and CMAKE is a cmake executable to be used for compilation. Please see install.sh script directly for more details on the user arguments.

# RUNNING THE PROGRAM

## Executing the program
To run the program go to the {INSTALL_DIRECTORY}/bin directory and run
* ./XxxDisplay_CodeParser -f {input_file.txt} -d {output_directory}

where 

* {input_file.txt} is a name of the file to be processed
* {output_directory} is a directory where the PNG images will be saved. Please note that the {output_directory} must exists before the program executes, 
otherwise an exception will be thrown.

## Logs 

The program will log basic information about its input file and output directory as well as any eventual errors detected into the simple log file saved in the run time directory.

## Exit Codes

The program can terminate with following exit codes:
   - 0 - program finished sucesfully and no error was detected,
   - 1 - program encountered an error in the input file,
   - 2 - an error from the libpng library has occured while saving the PNG image,
   - 3 - an error happend when opening the file for writing, most likely the parent directory does not exist or a program does not have writing rights for the perent directory 
   - 4 - a program could not initiate a log file,
   - 5 - no destination directory has been specified by the user,
   - 6 - unknown and unexpected exception has occured,

## Help message

To display the help message run
* ./XxxDisplay_CodeParser -h

# THIRD PARTY LIBRARIES
This program uses following third party libraries.

* spdlog for logging, v2: https://github.com/gabime/spdlog
* cxxopts for handling input arguments, v2.1: https://github.com/jarro2783/cxxopts
* CATCH2 unit test library, v2.13: https://github.com/catchorg/Catch2

Supported copies of these libraries are contained within this repository. 

Furtheer more the following system library is required:
* libpng 1.6.37

# TROUBLESHOOTING

## Error:

> Installing spdlog.
>
> Warning: removing previous spdlog build in /home/rctbg2/test_folder/bots_and_us_solutions/third_party/spdlog/build
> CMake Error: The source directory "" does not exist.
> Specify --help for usage, or press the help button on the CMake GUI.<cite>

Solution:
It means that the CMake version used is to old. Please update the CMake

## Error: 
> fatal error: filesystem: No such file or directory
> #include <filesystem>

Solution:
Filesystem is a C++17 addition. This error means that the gcc version does not support C++17. Please update the gcc.
 
# FURTHER WORK
 
XXX Display can support more than 10000 codes. It has seven segments per character, so it can support up to 7^2=49 different symbols per character and 49^6 different segment combinations (or 49^4 without modifying the checksum).
 
Even though some of these combinations may not be valid (0000 0000) or may not work well with the OCR system, new combinations of segments could be agreed upon to represent the higher values. E.g.,
 * 10 - A - 1110 0111
 * 11 - B - 1111 0001
 * 12 - C - 0011 0101
 * ...
 
Other, more abstract symbols could be used as well if required.
 
Then the new symbols should be added to the 'bitMap_' member of the XxxDisplay class. No other change would be required in the XxxDisplay class.
 
The checksum mod97 method would have to be updated to accept non-digit characters and perform its computation in an X-base, where X is a number of supported characters. A different modulo operator may be required. The std::stoi method that translates the string digit into the numerical value supports non-10-base computations by default. From cppreference:
 
 > The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits include alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer. The case of the characters is ignored. 
 
 No changes in the BuissnessLayer class would be required.
 
 

 
