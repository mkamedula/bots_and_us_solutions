# Code Parser for XXX Display 

This repository contains software to process an input file of 4-digit codes to PNG images understandable by XXX Displays.

Input files are expected to be pure text files, where each line consists of a 4-digit number (a code), and no other character is present in the text file.

For each code, a 97 mod checksum is prepended to the number. It results in a 6-digit code. For each 6-digit number, a PNG image is generated. This PNG image can be sent to the XXX Display to display the generated code. Each file is named based on the 4-digit initial code, e.g. a code '8420' will result in an output file '8420.png'. All files are saved to the directory specified as an input argument to the program.


# INSTALL

## Minimum requirements (Tested set-up)

* CMake 3.21
* gcc 10.3
* libpng 1.6.37
* Ubuntu 20.04.4 LTS

## Installation procedure:

To install the program - minimum CMake 3.21:

* download this repository
  * git clone https://github.com/mkamedula/bots_and_us_solutions
* go to the install_script directory inside the git repo directory
* add executable permissions to the installation script.
  * chmod +x ./install.sh
* run the installation script. Please be aware that at least CMake 3.21 is required for the script to execute correctly. The script will install all third-party libraries that are not mentioned in the minimum requirements section (see Third party libraries section), and the code itself
  * ./install.sh
* By default, the script will install the files to the ${GIT_ROOT_DIR}/install directory, where GIT_ROOT_DIR is a root directory of this repository. If you want to change the installation directory, you can do it using the input arguments
  * ./install.sh {CLEAN} {INSTALL_DIRECTORY} {CMAKE_BUILD_TYPE}, where CLEAN takes true/false values and defines whether the clean build should be performed. Please see install.sh script directly for more details on the user arguments.

# RUNNING THE PROGRAM

To run the program go to the {INSTALL_DIRECTORY}/bin directory and run
* ./XxxDisplay_CodeParser -f {input_file.txt} -d {output_directory}

where 

* {input_file.txt} is a name of the file to be processed
* {output_directory} is a directory where the PNG images will be saved. Please note that the {output_directory} must exists before the program executes, 
otherwise an exception will be thrown.

The program will log basic information about its input file and output directory as well as any eventual errors detected into the simple log file save in the run time directory.

The program can terminate with following exit codes:
   - 0 - program finished sucesfully and no error was detected,
   - 1 - program encountered an error in the input file,
   - 2 - an error from the libpng library has occured while saving the PNG image,
   - 3 - an error happend when opening the file for writing, most likely the parent directory does not exist or a program does not have writing rights for the perent directory 
   - 4 - a program could not initiate a log file,
   - 5 - no destination directory has been specified by the user,
   - 6 - unknown and unexpected exception has occured,

To display the help message run
* ./XxxDisplay_CodeParser -h

# Third party libraries
This program uses following third party libraries.

* spdlog for logging, v2: https://github.com/gabime/spdlog
* cxxopts for handling input arguments, v2.1: https://github.com/jarro2783/cxxopts
* CATCH2 unit test library, v2.13: https://github.com/catchorg/Catch2

Supported copies of these libraries are contained within this repository. 

Furtheer more the following system library is required:
* libpng 1.6.37
