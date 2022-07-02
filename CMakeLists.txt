cmake_minimum_required(VERSION 3.21)
PROJECT(Code_Parser VERSION 0.1.0)

MESSAGE(STATUS "Compiling Code Parser")

include(GNUInstallDirs)

set(EXT_LIBS_PATH "${CMAKE_INSTALL_PREFIX}")

find_package(spdlog CONFIG REQUIRED HINTS ${EXT_LIBS_PATH} NO_DEFAULT_PATH)

add_library(${CMAKE_PROJECT_NAME}
        src/code_parser.cpp
        )
#add_library(namespace::${CMAKE_PROJECT_NAME}} ALIAS ${CMAKE_PROJECT_NAME}})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/template>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
        spdlog::spdlog
        )

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC
        cxx_std_17
        )

install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${CMAKE_PROJECT_NAME}Config.cmake.in"
        "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/cmake
        PATH_VARS CMAKE_INSTALL_DATAROOTDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR
)

write_basic_package_version_file("${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(EXPORT ${CMAKE_PROJECT_NAME}_Targets
        FILE ${CMAKE_PROJECT_NAME}Targets.cmake
#        NAMESPACE test
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/template/ DESTINATION include/)

#
#add_executable(codeParser main.cpp)
#
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    find_package(Catch2 2 REQUIRED NO_MODULE PATHS ${EXT_LIBS_PATH} NO_DEFAULT_PATH)

    add_executable(${CMAKE_PROJECT_NAME}_tests
            test/main_test.cpp
            test/src/input_file_tests.cpp
            test/src/checksum_test.cpp
            test/src/bit_code_tests.cpp
            test/src/pixel_code_test.cpp
            )

    target_link_libraries(${CMAKE_PROJECT_NAME}_tests PRIVATE
            ${CMAKE_PROJECT_NAME}
            Catch2::Catch2
            )

    include(CTest)
    include(Catch)
    catch_discover_tests(${CMAKE_PROJECT_NAME}_tests)

    add_custom_command(
            TARGET ${CMAKE_PROJECT_NAME}_tests
            COMMENT "Run tests"
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failures
    )
endif ()