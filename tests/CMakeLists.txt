### Tests ###

# Variables Definition
set(TESTS_SRC_DIR ${TESTS_DIR}/source)

# Unit Tests #
# Program behavior
add_subdirectory(${TESTS_SRC_DIR})

# TestTstring
add_subdirectory(${TESTS_SRC_DIR}/utils/tchar)

# TestProcess
add_subdirectory(${TESTS_SRC_DIR}/process)