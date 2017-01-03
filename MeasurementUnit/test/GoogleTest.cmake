# This module downloads and compiles Googletest and Googlemock.
#
# Static library paths are stored in the following variables:
# GMOCK_LIB_PATH 
# GMOCK_MAIN_PATH
# GTEST_LIB_PATH 


set(GMOCK_EXTERNAL_CMAKE_ARGS "")

# pass toolchain file to external project if one is set
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    set(TOOLCHAIN_FILE_LOCATION "${CMAKE_TOOLCHAIN_FILE}")

    set(GMOCK_EXTERNAL_CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE_LOCATION}")
    message(STATUS "Passing toolchain file ${TOOLCHAIN_FILE_LOCATION} to gtest external project.")
endif(DEFINED CMAKE_TOOLCHAIN_FILE)


# Enable ExternalProject CMake module
include(ExternalProject)

# Download GoogleTest from Github
ExternalProject_Add(
    gtest_external
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "release-1.8.0"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/gmock
    INSTALL_COMMAND "" # Disable install step
    CMAKE_ARGS ${GMOCK_EXTERNAL_CMAKE_ARGS}
)

# Get the directory where 'ExternalProject' placed the gmock sources
ExternalProject_Get_Property(gtest_external source_dir binary_dir)


set(GMOCK_LIB_PATH "${binary_dir}/googlemock/libgmock.a")
set(GMOCK_MAIN_PATH "${binary_dir}/googlemock/libgmock_main.a") # Can be used to link in the standaard GoogleMock main()
set(GTEST_LIB_PATH "${binary_dir}/googlemock/gtest/libgtest.a")
set(GTEST_MAIN_PATH "${binary_dir}/googlemock/gtest/libgtest_main.a")# Can be used to link in the standaard GoogleTest main()

include_directories(
    "${source_dir}/googletest/include"
    "${source_dir}/googlemock/include"
)

