#include <gtest/gtest.h>
#include <filesystem>

#include <libutils/files.hpp>
#include "paths.test.files.hpp"

/**
 * ReadDirectory tests.
 */

namespace fs = std::filesystem;

/****
 * ReadDirectoryOutputIt tests. *
 ****/

TEST(ReadDirectoryOutputIt, ReadsDirectory) {
  std::vector<fs::path> result;
  utils::read_directory(kDirPath, std::back_inserter(result));
  EXPECT_FALSE(result.empty());
}

TEST(ReadDirectoryOutputIt, InvalidDirectoryPath) {
  std::vector<fs::path> result;
  EXPECT_THROW(utils::read_directory("/invalid/path", std::back_inserter(result)),
               fs::filesystem_error);
}

TEST(ReadDirectoryOutputIt, DirectoryWithMultipleFiles) {
  //! [read_directory_output_it_start]
  std::vector<fs::path> result;
  utils::read_directory(kDirPath, std::back_inserter(result));
  std::sort(result.begin(), result.end());
  //! [read_directory_output_it_end]

  std::vector expected{fs::path(std::string(kDirPath) + "/a.txt"),
                       fs::path(std::string(kDirPath) + "/b.jpg"),
                       fs::path(std::string(kDirPath) + "/c.html")};
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(result, expected);
}

/*
 * ReadDirectoryIf tests.
 */

TEST(ReadDirectoryIf, CopiesPathsSatisfyingPredicate) {
  //! [read_directory_if_start]
  std::vector<std::filesystem::path> result;
  auto predicate = [](const std::filesystem::path &p) {
    return p.extension() == ".txt";
  };
  utils::read_directory_if(kDirPath, std::back_inserter(result), predicate);
  //! [read_directory_if_end]
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].extension(), ".txt");
}

TEST(ReadDirectoryIf, NoPathsSatisfyPredicate) {
  std::vector<std::filesystem::path> result;
  auto predicate = [](const std::filesystem::path &p) {
    return p.extension() == ".nonexistent";
  };
  utils::read_directory_if(kDirPath, std::back_inserter(result), predicate);
  EXPECT_TRUE(result.empty());
}

TEST(ReadDirectoryIf, EmptyDirectory) {
  std::vector<std::filesystem::path> result;
  auto predicate = [](const std::filesystem::path &p) { return true; };
#ifdef __GNUC__
  #ifndef __clang__
  EXPECT_THROW(utils::read_directory_if(kDirEmptyPath, std::back_inserter(result), predicate),
               std::filesystem::filesystem_error);
  #endif
  #ifdef __clang__
  utils::read_directory_if(kDirEmptyPath, std::back_inserter(result), predicate);
  EXPECT_TRUE(result.empty());
  #endif
#endif

}

TEST(ReadDirectoryIf, InvalidDirectoryPath) {
  const std::string path{"invalid_directory"};
  std::vector<std::filesystem::path> result;
  auto predicate = [](const std::filesystem::path &p) { return true; };
  EXPECT_THROW(
      utils::read_directory_if(path, std::back_inserter(result), predicate),
      std::filesystem::filesystem_error);
}

/****
 * ReadDirectoryContainer tests. *
 ****/

TEST(ReadDirectoryContainer, ReadsNonEmptyDirectory) {
  const auto result{
      utils::read_directory<std::vector<std::filesystem::path>>(kDirPath)};
  EXPECT_FALSE(result.empty());
}

TEST(ReadDirectoryContainer, InvalidDirectoryPath) {
  EXPECT_THROW(
      utils::read_directory<std::vector<std::filesystem::path>>("/invalid/path"),
      std::filesystem::filesystem_error);
}

TEST(ReadDirectoryContainer, DirectoryWithMultipleFiles) {
  //! [read_directory_container_start]
  auto result{
      utils::read_directory<std::vector<std::filesystem::path>>(kDirPath)};
  std::sort(result.begin(), result.end());
  //! [read_directory_container_end]

  std::vector expected{fs::path(std::string(kDirPath) + "/a.txt"),
                       fs::path(std::string(kDirPath) + "/b.jpg"),
                       fs::path(std::string(kDirPath) + "/c.html")};
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(result, expected);
}

/****
 * ReadDirectoryIfContainer tests.
 ****/

TEST(ReadDirectoryIfContainer, CopiesPathsSatisfyingPredicate) {
  //! [read_directory_if_container_start]
  auto predicate = [](const std::filesystem::path &p) {
    return p.extension() == ".txt";
  };
  const auto result{utils::read_directory_if(kDirPath, predicate)};
  //! [read_directory_if_container_end]
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].extension(), ".txt");
}

TEST(ReadDirectoryIfContainer, NoPathsSatisfyPredicate) {
  auto predicate = [](const std::filesystem::path &p) {
    return p.extension() == ".nonexistent";
  };
  const auto result{utils::read_directory_if(kDirPath, predicate)};
  EXPECT_TRUE(result.empty());
}

TEST(ReadDirectoryIfContainer, EmptyDirectory) {
  auto predicate = [](const std::filesystem::path &p) { return true; };
#ifdef __GNUC__
  #ifndef __clang__
  EXPECT_THROW(utils::read_directory_if(kDirEmptyPath, predicate),
               std::filesystem::filesystem_error);
  #endif
  #ifdef __clang__
  const auto result{utils::read_directory_if(kDirEmptyPath, predicate)};
  EXPECT_TRUE(result.empty());
  #endif
#endif
}

TEST(ReadDirectoryIfContainer, InvalidDirectoryPath) {
  const std::string path{"invalid_directory"};
  auto predicate = [](const std::filesystem::path &p) { return true; };
  EXPECT_THROW(utils::read_directory_if(path, predicate),
               std::filesystem::filesystem_error);
}
