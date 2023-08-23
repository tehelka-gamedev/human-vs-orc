# CMakeLists.txt for the main project


file(GLOB_RECURSE SRC_HEADERS
    "**.h"
)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${SRC_HEADERS})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Set the binary output name based on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}_Debug")
else()
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}_Release")
endif()


