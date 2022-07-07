cmake_minimum_required(VERSION 3.21)
PROJECT(XxxDisplay_CodeParser VERSION 0.1.0)

MESSAGE(STATUS "Compiling XxxDisplay_CodeParser")

include(GNUInstallDirs)

set(EXT_LIBS_PATH "${CMAKE_INSTALL_PREFIX}")

find_package(cxxopts CONFIG REQUIRED HINTS ${EXT_LIBS_PATH} NO_DEFAULT_PATH)
find_package(spdlog CONFIG REQUIRED HINTS ${EXT_LIBS_PATH} NO_DEFAULT_PATH)

add_library(${CMAKE_PROJECT_NAME}_lib
        src/hardware.cpp
        src/exceptions.cpp
        src/business_logic.cpp
        src/utils.cpp
        )

target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/template>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(${CMAKE_PROJECT_NAME}_lib
        PRIVATE
        png
        )

target_compile_features(${CMAKE_PROJECT_NAME}_lib PUBLIC
        cxx_std_17
        )

install(TARGETS ${CMAKE_PROJECT_NAME}_lib
        EXPORT ${CMAKE_PROJECT_NAME}_lib_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${CMAKE_PROJECT_NAME}_libConfig.cmake.in"
        "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_libConfig.cmake"
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/cmake
        PATH_VARS CMAKE_INSTALL_DATAROOTDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR
)

write_basic_package_version_file("${CMAKE_PROJECT_NAME}_libConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(EXPORT ${CMAKE_PROJECT_NAME}_lib_Targets
        FILE ${CMAKE_PROJECT_NAME}_libTargets.cmake
        #        NAMESPACE test
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_libConfig.cmake"
        "${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}_libConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/template/ DESTINATION include/)


add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/template>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
        cxxopts::cxxopts
        spdlog::spdlog
        ${CMAKE_PROJECT_NAME}_lib
        )

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC
        cxx_std_17
        )

install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    find_package(Catch2 2 REQUIRED NO_MODULE PATHS ${EXT_LIBS_PATH} NO_DEFAULT_PATH)

    add_executable(${CMAKE_PROJECT_NAME}_tests
            test/main_test.cpp
            test/src/business_logic_test.cpp
            test/src/checksum_test.cpp
            test/src/hardware_test.cpp
            test/src/save_png_test.cpp
            test/src/support_methods.cpp
            )

    target_link_libraries(${CMAKE_PROJECT_NAME}_tests PRIVATE
            ${CMAKE_PROJECT_NAME}_lib
            Catch2::Catch2
            )

    target_include_directories(${CMAKE_PROJECT_NAME}_tests PRIVATE
            test/include
            )

    include(CTest)
    include(Catch)
    catch_discover_tests(${CMAKE_PROJECT_NAME}_tests)
#
#    add_custom_command(
#            TARGET ${CMAKE_PROJECT_NAME}_tests
#            COMMENT "Run tests"
#            POST_BUILD
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failures
#    )
endif ()