#!/bin/bash

# Build the release version of the project.
# This script is used by the CI/CD pipeline.

# Calling the script without the "run_tests" argument will not build the tests.

echo "Building the release version of the project..."

# Clean the build directory
rm -r build/release &> /dev/null

echo -n "Deciding whether tests should be build... "
if [ -n "$1" ]; then
  if [ "$1" == "run_tests" ]; then
    BUILD_TESTS="ON"
    echo "YES"
  fi
else
  BUILD_TESTS="OFF"
  echo "NO"
fi

cmake -S . --preset=release -DENABLE_TESTING="$BUILD_TESTS"
RESULT=$?

if [ $RESULT -ne 0 ]; then
  exit $RESULT
fi

echo "Finished building the release version of the project."

if [ "$(uname -s)" == "Linux" ]; then
  cpu_count=$(nproc)
elif [ "$(uname -s)" == "Darwin" ]; then
  cpu_count=$(sysctl -n hw.ncpu)
else
  exit 1
fi

echo "Building Release using ${cpu_count} threads..."
cmake --build build/release -j$"$cpu_count"
RESULT=$?

if [ $RESULT == 0 ]; then
  echo "SUCCESS: Release build succeeded."
else
  echo "FAIL: Release build failed."
fi
exit $RESULT
