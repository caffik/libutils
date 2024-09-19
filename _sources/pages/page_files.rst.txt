.. _page_files:

Files
=====

The **files** header file contains template functions that enables reading the directory content in efficient way.

.. doxygenfile:: files.hpp
    :project: libutils

Usage
-----

The following examples demonstrates how to use the **files** header file, but first let's define the namespace alias:

.. code-block:: cpp

    namespace fs = std::filesystem;

Moreover, we assume that `kDirPath` is a valid directory path and contains the following files:
* `a.txt`,
* `b.jpg`,
* `c.html`.

- ``read_directory``

.. literalinclude:: ../../../tests/test.files.cpp
    :language: cpp
    :start-after: read_directory_output_it_start
    :end-before: read_directory_output_it_end
    :dedent: 2
    :append:
        std::cout << "result: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }

Output:

.. code-block:: none

    result: a.txt b.jpg c.html

- ``read_directory_if``

.. literalinclude:: ../../../tests/test.files.cpp
    :language: cpp
    :start-after: read_directory_if_start
    :end-before: read_directory_if_end
    :dedent: 2
    :append:
        std::cout << "result: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }

Output:

.. code-block:: none

    result: a.txt

- ``read_directory<typename Container>``

.. literalinclude:: ../../../tests/test.files.cpp
    :language: cpp
    :start-after: read_directory_container_start
    :end-before: read_directory_container_end
    :dedent: 2
    :append:
        std::cout << "result: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }

Output:

.. code-block:: none

    result: a.txt b.jpg c.html

- ``read_directory_if<typename Container>``

.. literalinclude:: ../../../tests/test.files.cpp
    :language: cpp
    :start-after: read_directory_if_container_start
    :end-before: read_directory_if_container_end
    :dedent: 2
    :append:
        std::cout << "result: ";
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }

Output:

.. code-block:: none

    result: a.txt

