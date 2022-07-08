# bots_and_us_solutions
This repository contains a software to process an input file of 4-digit codes to a PNG images understandable by XXX Displays.

Input files are expected to be pure text files, where each line consists of a 4-digit number (a code) and no other character is present in the text file.

For each code, a 97 mod checksum is prepend at the begining of the number. It results in a 6-digit code. For each 6-digit number, a PNG image is generated. This PNG image can be sent to the XXX Display to display the 6-digit number. Each file is named based on the 4-digit initial code, e.g. a code 8420 will result in a output file 8420.png. All files are saved to the directory specifed as an input argument to the program.


# INSTALL

## Minimum requirements (Tested set-up)

* CMake 3.21
* gcc 10.3
* libpng 1.6.37
* Ubuntu 20.04.4 LTS

## Installation procedure:

To install the program:

* download this repository
  * git clone https://github.com/mkamedula/bots_and_us_solutions
* go to the install_script directory inside the git repo directory
* add executable permissions to the installation script
  * chmod +x ./install.sh
* run the installation script. It will install all third-party libraries that are not mentioned in the minimum requirements section, and the code itself
  * ./install.sh
* By default, the script will install the files to the ${GIT_ROOT_DIR}/install directory, where GIT_ROOT_DIR is a root directory of this repository. If you want to change the installation directory, you can do it using the input arguments
  * ./install.sh {CLEAN} {INSTALL_DIRECTORY} {CMAKE_BUILD_TYPE}, where CLEAN takes true/false values and defines whether the clean build should be performed. Please see install.sh script directly for more details on the user arguments.

# RUNNING THE PROGRAM

To run the program go to the {INSTALL_DIRECTORY}/bin used when installing the program. And run
* ./XxxDisplay_CodeParser -f {input_file.txt} -d {output_directory}

where 

* {input_file.txt} is a name of the file to be processed
* {output_directory} is a directory where the PNG images will be saved. Please note that the {output_directory} must exists before the program executes, 
otherwise an exception will be thrown.

The program will log basic information about its input file and output directory as well as any eventual errors detected into the simple log file save in the run time directory.

The program can terminate with following exit codes:
   - SUCCESS = 0,
   - INPUT_FILE_ERROR = 1,
   - LIBPNG_ERROR = 2,
   - SAVE_FILE_ERROR = 3,
   - SPDLOG_INIT_ERROR = 4,
   - UNKNOWN_DESTINATION_POINT = 5,
   - UNKNOWN_EXCEPTION = 6,

To display the help message run
* ./XxxDisplay_CodeParser -h

# Third party libraries
This program uses a following third party libraries.

* spdlog for logging: https://github.com/gabime/spdlog
* cxxopts for handling input arguments: https://github.com/jarro2783/cxxopts
* CATCH2 unit test library: https://github.com/catchorg/Catch2

Supported and tested copies of these libraries are contained within this repository. 

Furtheer more the following system library is required:
* libpng 1.6.37
