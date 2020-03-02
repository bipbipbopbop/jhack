### TestTstring ###
add_executable(TestTstring)

## construct source files list
set(TESTTSTRING_SRC
   tstring.hpp
   io.hpp
)
list(TRANSFORM TESTTSTRING_SRC PREPEND ${SRC_DIR}/utils/tchar/)
list(APPEND TESTTSTRING_SRC
     ${TESTS_SRC_DIR}/utils/tchar/tstring.cpp
)

## add Source files
target_sources(TestTstring PRIVATE ${TESTTSTRING_SRC})
target_include_directories(TestTstring PRIVATE
                           ${CMAKE_SOURCE_DIR}
                           ${SRC_DIR}
                           ${TESTS_SRC_DIR}
)
unset(TESTTSTRING_SRC)

add_test(NAME Tstring COMMAND TestTstring)
set_tests_properties(Tstring PROPERTIES
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PASS_REGULAR_EXPRESSION "test1  test2\t\tstuff"
)
