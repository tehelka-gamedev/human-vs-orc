# CMakeLists for the TestProject


# find google test package
find_package(GTest)

# if not found, download and build it
if(NOT GTEST_FOUND)
    message(STATUS "GTest package not found. Downloading and building it from git source.")
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Build the downloaded googletest package
if (NOT GTEST_FOUND)
message(STATUS "Building GTest package")
    FetchContent_MakeAvailable(googletest)
endif()

file(GLOB TEST_SRC_FILES
    "**.cpp"
)

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SRC_FILES})

# Link the tests with Google Test
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE GTest::gtest_main)

# Add the "src" directory to include paths for the tests
target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../${SOURCE_DIR})

# Remove the "src/main.cpp" file from the test sources
list(FILTER SRC_FILES EXCLUDE REGEX "${SOURCE_DIR}/main.cpp$")

# Add the sources to the test executable
target_sources(${TEST_EXECUTABLE_NAME} PRIVATE ${SRC_FILES})
