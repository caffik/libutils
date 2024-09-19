.. libutils

libutils
========

`libutils` is a C++ utility library that provides a set of useful functions and templates to simplify common programming
tasks. The library is designed to be lightweight and not difficult to integrate into various projects.

Installation:
#############

The easiest way to use the library is to copy the header files into project and include it in source code.

But it is recommended to include the library with CMake. For that purposes `FetchContent` module can be used:

.. code-block:: cmake

    include(FetchContent)
    FetchContent_Declare(
        libutils
        GIT_REPOSITORY  https://github.com/caffik/libutils.git
        GIT_TAG         v1.1.2
    )
    FetchContent_MakeAvailable(libutils)
    include(libutils)
    target_link_libraries(${PROJECT_NAME} PRIVATE libutils::main)

CMake Options:
**************

- `ENABLE_TESTING` - build tests for the library. Default is `OFF`.
- `ENABLE_DOCS` - build documentation for the library. Default is `OFF`.

Documentation:
##############

The documentation is organized in a set of pages, each one containing a description of a header file and examples of usage.
Documentation is generated with Doxygen, Sphinx and Breathe. The source code of the documentation is located in the `docs` folder.

Documentation requires the following dependencies:

- breathe (>= 4.35.0)
- Doxygen (>= 1.11.0)
- sphinx (>= 8.0.2)

Contents:
#########

.. toctree::
   :maxdepth: 1

   pages/page_algorithm
   pages/page_files
   pages/page_iterator
   pages/page_numeric
   pages/page_type_traits
   pages/page_tuple
   pages/page_utility
