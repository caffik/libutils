# libutils

## Overview

`libutils` is a C++ utility library that provides a set of useful functions and templates to simplify common programming
tasks. The library is designed to be lightweight and not difficult to integrate into various projects.

### Requirements

- C++17 or later
- CMake 3.28 or later

## Project Structure

- `docs/`: Contains the documentation for the library.
- `include/`: Contains the public headers for the library.
- `tests/`: Contains unit tests for the library.

### Description

`libutils` includes the following header files:

- `utils/algorithm.hpp`: includes functions for finding the index of the maximum element in a range, copying a range of
  elements multiple times, finding the first position where two ranges differ starting from the end, and reordering
  elements in a range based on given indices. The file uses templates to work with different types of iterators and
  predicates. 
<p></p> 

- `utils/files.hpp`: provides functionality for reading the contents of a directory and filtering the paths based on a
  given condition. It uses templates to allow flexibility in the types of containers and predicates used.
<p></p> 

- `utils/iterator.hpp`: provides utilities for working with iterators, including functions to advance multiple
  iterators, compute distance differences between ranges, and determine the longer range between two ranges. It also
  includes a MultiIterator class template for iterating over multiple iterators simultaneously.
<p></p> 

- `utils/numeric.hpp`: contains functions to compute the product and mean of a range of elements. These functions are
  designed to work with various types of input iterators.
<p></p> 

- `utils/tuple.hpp`: provides utilities for working with tuples, including functions to move, swap, and copy elements
  between tuples. It also includes a pointer_tuple class template that holds a tuple of pointers to elements, allowing
  for operations on the elements pointed to by the pointers.
<p></p> 

- `utils/type_traits.hpp`: includes functionality for checking if a type has a push_back or insert method, removing
  const, volatile, and reference qualifiers from a type, and invoking a series of functions on a copy of a given
  argument.
<p></p> 

- `utils/utility.hpp`: provides general utility functions, such as a function to get a reference to a value or
  dereferenced pointer and a function to execute a given function in a compile-time loop. These utilities are designed
  to simplify common programming tasks and improve code readability.

## Installation

### Using CMake:

To add `libutils` to your project, you can use CMake's `add_subdirectory` function. First, clone the repository:

```sh
git clone https://github.com/caffik/libutils.git
```

Then, add the following lines to your `CMakeLists.txt`:

```cmake
add_subdirectory(libutils)
target_link_libraries(your_target PRIVATE libutils::main)
```

It can be also added with `FetchContent`:

```cmake
include(FetchContent)
FetchContent_Declare(
    libutils
    GIT_REPOSITORY https://github.com/caffik/libutils.git
    GIT_TAG v1.1.2 
)
FetchContent_MakeAvailable(libutils)
```

#### CMake options:
- `ENABLE_TESTING`: build the tests for the library (default: `OFF`)
- `ENABLE_DOCS`: build the documentation for the library (default: `OFF`) 

### Manual installation:

Clone the repository:
    
```sh
git clone https://github.com/caffik/libutils.git
```

Add the `include` directory to your project's include path. Then include the desired header files in your source files:

```cpp
#include <utils/algorithm.hpp>
#include <utils/files.hpp>
```

## Documentation

The documentation is generated using Doxygen and Sphinx. It is built automatically by CMake. <br/> 
Documentation page: [libutils](https://caffik.github.io/libutils/)
### Requirements:
- `breathe` (>= 4.35.0)
- `Doxygen` (>= 1.11.0)
- `sphinx` (>= 8.0.2)

## Examples

Examples of how to use the library can be found on the library page.



  

