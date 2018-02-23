project(tests)

# Add GoogleTest
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add tests sources
add_executable(runTests
        tests_lexer.cpp
        )

# Add dependencies
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests YAP)
