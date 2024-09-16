include(FetchContent)

#######################
#   Configure files   #
#######################

set(TEST_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test_files")
configure_file(priv/paths.test.files.hpp.in
        ${CMAKE_CURRENT_SOURCE_DIR}/paths.test.files.hpp)

###################
#   Google Test   #
###################

enable_testing()

find_package(GTest 1.14.0
        QUIET
)

if (NOT GTest_FOUND)
    message(STATUS "GTest NOT found. Fetching content...")
    set(BUILD_GMOCK OFF)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.15.2
    )

    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)
endif()

#################
#   Set Tests   #
#################

add_executable(Tests
        test.algorithm.cpp
        test.files.cpp
        test.iterator.cpp
        test.numeric.cpp
        test.tuple.cpp
        test.type_traits.cpp
        test.utility.cpp
)

target_link_libraries(Tests
        PRIVATE
        GTest::gtest_main
        libutils::main
)

gtest_discover_tests(Tests)
