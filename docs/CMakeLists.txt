find_package(
  Python
    REQUIRED
    COMPONENTS Interpreter 
)

find_package(
  Doxygen 1.11.0
    REQUIRED
)

execute_process(
  COMMAND make html
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_QUIET
)