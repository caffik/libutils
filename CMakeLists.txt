###############
#   OPTIONS   #
###############

option(ENABLE_TESTING "Build tests." ON)

###############
#   PROJECT   #
###############

cmake_minimum_required(VERSION 3.20)
project(libutils
    VERSION 1.0.0
    DESCRIPTION "Utils library."
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/libutils
)

######################
#   libutils::main   #
######################

add_library(libutils_main INTERFACE)
add_library(libutils::main ALIAS libutils_main)

target_include_directories(
    libutils_main
        INTERFACE
            $<BUILD_INTERFACE:${INCLUDE_DIR}>
)

######################
#   SUBDIRECTORIES   #
######################

if(ENABLE_TESTING)
    add_subdirectory(tests)
endif()