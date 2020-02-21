### Tests ###

# Hello
add_executable(Hello)
target_link_libraries(Hello PRIVATE ${PROJECT_NAME})
target_sources(Hello PRIVATE
               ${TEST_SRC_DIR}/main.cpp
)

add_test(NAME Hello COMMAND Hello WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
set_tests_properties(Hello PROPERTIES
                     PASS_REGULAR_EXPRESSION "Hello World!"
)

# subdirectories
#...