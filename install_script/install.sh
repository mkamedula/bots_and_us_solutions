#!/bin/bash

# switch to the script directory
cd "$(dirname "$(realpath "$0")")";

ROOT_DIR=${PWD}/..

clean=${1:-false}
cmake=${2:-cmake}
BUILD_TYPE=${3:-Release}
INSTALL_ROOT="$(realpath ${4:-${ROOT_DIR}/install})"

install_library() {
  echo -e "\nInstalling ${library}.\n";
  cd ${ROOT_DIR}/third_party/${library}
  if [ -d "build" ] && [ "${clean}" = true ]; then
    echo "Warning: removing previous ${library} build in ${PWD}/build";
    rm -R build;
  fi
  if [ -d "install" ] && [ "${clean}" = true ]; then
      echo "Warning: removing previous ${library} install folder:  ${PWD}/install";
      rm -R install;
  fi

  ${cmake}  -Bbuild/${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT}/ -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${args}  || exit 1
  ${cmake}  --build build/${BUILD_TYPE} --target install -- -j $(nproc)  || exit 1
}

library=spdlog
args="-DSPDLOG_BUILD_BENCH=FALSE -DSPDLOG_BUILD_TESTS=FALSE"
install_library || exit 1

library=Catch2
args="-DBUILD_TESTING=OFF
      -DCATCH_INSTALL_DOCS=OFF"
install_library || exit 1

echo "Install code parser"

cd ${ROOT_DIR}
if [ -d build/${BUILD_TYPE} ] && [ "${clean}" = true ]; then
  rm -R build/${BUILD_TYPE}
fi

${cmake} --preset ${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT}
${cmake} --build build/${BUILD_TYPE} --target install -- -j $(nproc)  || exit 1