#!/bin/bash

# This script handles installing an application. It installs the dependent targets and non-standard third-party
# libraries required by the application.
#
# The script takes three optional parameters
# 1 - should the build be cleaned before the installation. It applies all components including third-party libraries.
#     Default: false, Accepts: false, true
# 2 - installation directory for all components. Default: install folder in the project root directory
# 3 - value of the CMAKE_BUILD_TYPE and the CMake preset used to compile the main application. Default: Release,
#     Accepted: Release, Debug
# 4- specify custom cmake executable. Default: cmake, Accepted: any cmake executable

# switch to the script directory
cd "$(dirname "$(realpath "$0")")";

ROOT_DIR=${PWD}/..

CLEAN=${1:-false}
INSTALL_ROOT="$(realpath ${2:-${ROOT_DIR}/install})"
BUILD_TYPE=${3:-Release}
CMAKE=${4:-cmake}

# A function to handle standard installation of the third party library
install_library() {
  echo -e "\nInstalling ${library}.\n";
  cd ${ROOT_DIR}/third_party/${library}
  if [ -d "build" ] && [ "${CLEAN}" = true ]; then
    echo "Warning: removing previous ${library} build in ${PWD}/build";
    rm -R build;
  fi
  if [ -d "install" ] && [ "${CLEAN}" = true ]; then
      echo "Warning: removing previous ${library} install folder:  ${PWD}/install";
      rm -R install;
  fi

  ${CMAKE}  -Bbuild/${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT}/ -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${args}  || exit 1
  ${CMAKE}  --build build/${BUILD_TYPE} --target install -- -j $(nproc)  || exit 1
}

library=spdlog
args="-DSPDLOG_BUILD_BENCH=FALSE -DSPDLOG_BUILD_TESTS=FALSE"
install_library || exit 1

library=Catch2
args="-DBUILD_TESTING=OFF
      -DCATCH_INSTALL_DOCS=OFF"
install_library || exit 1

library=cxxopts
args=""
install_library || exit 1


echo "Install main code"

cd ${ROOT_DIR}
if [ -d build/${BUILD_TYPE} ] && [ "${CLEAN}" = true ]; then
  rm -R build/${BUILD_TYPE}
fi

${CMAKE} --preset ${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT}
${CMAKE} --build build/${BUILD_TYPE} --target install -- -j $(nproc)  || exit 1