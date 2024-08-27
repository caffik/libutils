cmake_minimum_required(VERSION 3.20)
project(
    utils 
    VERSION 1.0.0
    DESCRIPTION "Implementation of utils library."
    LANGUAGES CXX 
)

##########################
# Naming paths and files # 
##########################
set(UTILS_DIR 
  ${CMAKE_SOURCE_DIR}/libutils
)

set(INCLUDE_UTILS
  ${UTILS_DIR}/utilities.hpp
)

###############
# Set library # 
###############
add_library(libutils INTERFACE)
add_library(libutils::utils ALIAS libutils)

target_include_directories(
  libutils 
  INTERFACE 
  $<BUILD_INTERFACE:${INCLUDE_UTILS}>
)

######################
# Settings for tests # 
######################
set(CMAKE_TESTS ON CACHE STRING "Set whether tests should be build.")
if(CMAKE_TESTS)
    include(CTest)
    include(FetchContent)
    FetchContent_Declare(
      GoogleTest
      GIT_REPOSITORY  https://github.com/google/googletest.git
      GIT_TAG	        v1.14.0
    )

    FetchContent_MakeAvailable(GoogleTest)
    include(GoogleTest)
    
    set(TESTS_SOURCE
      ${UTILS_DIR}/utilities.test.cpp
    )
    
    add_executable(TESTS ${TESTS_SOURCE})
    target_link_libraries(TESTS PRIVATE libutils::utils GTest::gtest GTest::gtest_main GTest::gmock)
    target_compile_features(TESTS PRIVATE cxx_std_17)
    gtest_add_tests(TARGET TESTS)

endif()
