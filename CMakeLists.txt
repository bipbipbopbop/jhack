### Configuration ###
cmake_minimum_required(VERSION 3.0.0)

# Windows Specific requirement for shared library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(jhack VERSION 0.1.0)

# C++ Compilation specs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Main Target ###
add_library(${PROJECT_NAME} SHARED)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/source/")

# change output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# source files
set(SRC
    jhack.cpp
    process/MemoryScanner.cpp
    process/process.cpp
    window/window.cpp
    utils/getLastError.cpp
)
set(INC
    jhack.hpp
    process/MemoryScanner.hpp
    process/process.hpp
    process/pptr.hpp
    window/window.hpp
    utils/tchar.hpp
    utils/tchar/tstring.hpp
    utils/tchar/io.hpp
    utils/getLastError.hpp
)

list(TRANSFORM SRC PREPEND ${SRC_DIR})
list(TRANSFORM INC PREPEND ${SRC_DIR})

# build target
target_sources(${PROJECT_NAME} PRIVATE ${SRC} ${INC})
if(CMAKE_CXX_COMPILER_ID EQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -g)
endif()
# add header path as a dependency of the project
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${SRC_DIR}
)


### Tests ###
option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)
    add_subdirectory(${TESTS_DIR})
endif()