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




### OLD CMAKE FILE ###

# # Fetch google test
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)


# # Set coverage compilation option if in UNIX
# if (UNIX)
#     find_program(GCOV_PATH gcov REQUIRED)
#     # find_program(LCOV_PATH lcov REQUIRED)
#     set(CMAKE_CXX_FLAGS "--coverage")
# endif(UNIX)

# # # Locate Threads if in UNIX
# # find_package(Threads REQUIRED)
# # if (UNIX)
# # endif(UNIX)



# # Main project sources, without main
# file(GLOB_RECURSE SRC_FILES
#     "${SOURCE_DIR}/**.cpp"
# )
# list(REMOVE_ITEM SRC_FILES ${SRC_MAIN})

# # Tests sources
# file(GLOB GTESTS
#     "${TEST_DIR}/**.cpp"
# )


# # Allow include to use paths relative to project root
# include_directories(${PROJECT_SOURCE_DIR})

# enable_testing()


# # include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/include)

# ## Google Test setup


# add_executable(run_tests ${GTESTS} ${SRC_FILES})
# target_link_libraries(run_tests GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(run_tests)

# # create targets


# add_executable(HumanVSOrc ${SRC_MAIN} ${SRC_FILES})
# target_include_directories(${PROJECT_NAME} PRIVATE  ${PROJECT_SOURCE_DIR})
# # add_executable(run_tests ${GTESTS} ${SRC_FILES})

# # link run_tests to gtest (and pthread on Unix)
# # target_link_libraries(run_tests ${CMAKE_SOURCE_DIR}/build_gtest/lib/libgtest.a)

# if (UNIX)
#     # target_link_libraries(run_tests pthread)
# endif(UNIX)


