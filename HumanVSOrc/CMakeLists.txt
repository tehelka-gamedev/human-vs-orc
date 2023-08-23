cmake_minimum_required(VERSION 3.14)

project(HumanVSOrc)

# user variables
set(SOURCE_DIR "src" CACHE STRING "Directory containing the main project sources")
set(TEST_DIR "TestProject" CACHE STRING "Directory containing the unit testing sources")
set(EXECUTABLE_NAME "HumanVSOrc")
set(TEST_EXECUTABLE_NAME "TestProject")
set(BINARY_DIR "bin" CACHE STRING "Directory where the binaries will be saved")

file(GLOB_RECURSE SRC_FILES
    "${SOURCE_DIR}/**.cpp"
)

# Binaries will be saved there
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINARY_DIR})

set(CMAKE_CXX_STANDARD 17) # set Cpp17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # ensure compiler doesn't use non-standard extensions


# Set the build type to Release by default
# Build with cmake -DCMAKE_BUILD_TYPE=Release for debug build
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


enable_testing()


# Add the main project's source code
add_subdirectory(${SOURCE_DIR})

# Add the test project's source code
add_subdirectory(${TEST_DIR})
