### TestProcess ###
add_executable(TestProcess)

## construct source files list
set(TESTPROCESS_SRC
    ${TESTS_SRC_DIR}/process/process.cpp
    ${SRC_DIR}/process/process.cpp
    ${SRC_DIR}/process/process.hpp
    ${SRC_DIR}/utils/tchar.hpp
)

## add Source files
target_sources(TestProcess PRIVATE ${TESTPROCESS_SRC})
target_include_directories(TestProcess PRIVATE
                           ${CMAKE_SOURCE_DIR}
                           ${SRC_DIR}
                           ${TESTS_SRC_DIR}
)
unset(TESTPROCESS_SRC)

add_test(NAME Process COMMAND TestProcess)
set_tests_properties(Process PROPERTIES
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
