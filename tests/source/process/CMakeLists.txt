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


### TestPptr ###
add_executable(TestPptr)

## construct source files list
set(TESTPPTR_SRC
    ${TESTS_SRC_DIR}/process/pptr.cpp
    ${TESTS_SRC_DIR}/${TESTS_CONFIG_FILE}
    ${SRC_DIR}/process/pptr.hpp
)

## add Source files
target_sources(TestPptr PRIVATE ${TESTPPTR_SRC})
target_include_directories(TestPptr PRIVATE
                           ${CMAKE_SOURCE_DIR}
                           ${SRC_DIR}
                           ${TESTS_SRC_DIR}
)
unset(TESTPPTR_SRC)

add_test(NAME Pptr COMMAND TestPptr)
set_tests_properties(Pptr PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    REQUIRED_FILES ${TESTS_DATA_DIR}/deadbeef.exe
)