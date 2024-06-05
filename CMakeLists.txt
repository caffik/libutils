cmake_minimum_required(VERSION 3.20)
project(
    utils 
    VERSION 1.0.0
    DESCRIPTION "Implementation of utils library."
    LANGUAGES CXX 
)

set(NAMESPACE_NAME "libutils")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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
add_library(${PROJECT_NAME} INTERFACE)
add_library(${NAMESPACE_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  PUBLIC_HEADER ${INCLUDE_UTILS}
)

target_sources(${PROJECT_NAME}
  INTERFACE 
    $<BUILD_INTERFACE:${INCLUDE_UTILS}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(
  ${PROJECT_NAME} 
  INTERFACE 
    $<BUILD_INTERFACE:${INCLUDE_UTILS}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#########################
# Install configuration #
#########################
 
set(ConfigPackageLocation "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library 
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Library
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} COMPONENT Development 
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${NAMESPACE_NAME}::
  DESTINATION ${ConfigPackageLocation}
  COMPONENT Development
)

configure_package_config_file(
  ${PROJECT_NAME}Config.cmake.in
  ${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION "${ConfigPackageLocation}"
  PATH_VARS CMAKE_INSTALL_PREFIX
)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Development
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