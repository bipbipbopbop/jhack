### Configuration ###
cmake_minimum_required(VERSION 3.0.0)

project(jhack VERSION 0.1.0)

# C++ Compilation specs
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### Main Target ###
add_library(${PROJECT_NAME} SHARED)
set(SRC_DIR "source/")

# source files
set(SRC
    jhack.cpp
)
set(INC)

list(TRANSFORM SRC PREPEND ${SRC_DIR})
list(TRANSFORM INC PREPEND ${SRC_DIR})

# build target
target_sources(${PROJECT_NAME} PRIVATE ${SRC} ${INC})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -g)

# add header path as a dependency of the project
target_include_directories(${PROJECT_NAME} INTERFACE
                           ${SRC_DIR}
)


### Tests ###
option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    set(TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/tests/source)
    add_subdirectory(${TEST_SRC_DIR})
endif()


### Installer ###
# Maybe one day ?