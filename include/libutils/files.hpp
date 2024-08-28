#ifndef FILES_HPP
#define FILES_HPP

#include <filesystem>
#include "type_traits.hpp"

namespace utils {

/**
 * Reads the contents of a directory and copies the paths to an output iterator.
 *
 * @tparam OutputIt Type of the output iterator.
 * @param path Path to the directory to be read.
 * @param first Output iterator to which the directory contents will be copied.
 * @return Output iterator pointing to the end of the copied range.
 */
template <typename OutputIt>
OutputIt read_directory(const std::string &path, OutputIt first) {
  namespace fs = std::filesystem;
  auto dir_iter{fs::directory_iterator{path}};
  return std::copy(dir_iter, fs::directory_iterator{}, first);
}

/**
 * Reads the contents of a directory and copies the paths that satisfy a given
 * predicate to an output iterator.
 *
 * @tparam OutputIt Type of the output iterator.
 * @tparam UnaryPred Type of the unary predicate.
 * @param path Path to the directory to be read.
 * @param first Output iterator to which the directory contents will be copied.
 * @param p Unary predicate that returns true for the elements to be copied.
 * @return Output iterator pointing to the end of the copied range.
 */
template <typename OutputIt, typename UnaryPred>
OutputIt read_directory_if(const std::string &path, OutputIt first,
                           UnaryPred p) {
  namespace fs = std::filesystem;
  auto dir_iter{fs::directory_iterator{path}};
  return std::copy_if(dir_iter, fs::directory_iterator{}, first, p);
}

/**
 * Reads the contents of a directory and returns them in a container.
 *
 * @tparam Container Type of the container to store the directory contents.
 * Defaults to std::vector<std::filesystem::path>.
 * @param directory Path to the directory to be read.
 * @return A container with the paths of the directory contents.
 */
template <typename Container = std::vector<std::filesystem::path>>
Container read_directory(const std::string &directory) {
  namespace fs = std::filesystem;
  return Container(fs::directory_iterator(directory), fs::directory_iterator{});
}

/**
 * Reads the contents of a directory and copies the paths that satisfy a given
 * predicate to a container.
 *
 * @tparam Container Type of the container to store the directory contents.
 * Defaults to std::vector<std::filesystem::path>.
 * @tparam UnaryPred Type of the unary predicate.
 * @param path Path to the directory to be read.
 * @param p Unary predicate that returns true for the elements to be copied.
 * @return A container with the paths of the directory contents that satisfy the
 * predicate.
 */
template <typename Container = std::vector<std::filesystem::path>,
          typename UnaryPred>
Container read_directory_if(const std::string &path, UnaryPred p) {
  namespace fs = std::filesystem;
  Container result;
  auto dir_iter{fs::directory_iterator{path}};
  if constexpr (has_insert<Container>::value) {
    std::copy_if(dir_iter, fs::directory_iterator{},
                 std::inserter(result, result.end()), p);
    return result;
  }
  std::copy_if(dir_iter, fs::directory_iterator{}, std::back_inserter(result),
               p);
  return result;
}
} // namespace utils

#endif //FILES_HPP
