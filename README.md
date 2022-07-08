# bots_and_us_solutions
This repository contains a solution code for the for BotsAndUs application coding challenge

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
  * ./install.sh ${CLEAN} ${INSTALL_DIRECTORY} ${CMAKE_BUILD_TYPE}, where CLEAN takes true/false values and defines whether the clean build should be performed. Please see install.sh script directly for more details on the user arguments.


# Third party libraries
