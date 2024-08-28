#!/bin/bash

# Run the tests of the project.

if [ "$(uname -s)" == "Linux" ]; then
  cpu_count=$(nproc)
elif [ "$(uname -s)" == "Darwin" ]; then
  cpu_count=$(sysctl -n hw.ncpu)
else
  exit 1
fi

echo "Running tests using ${cpu_count} threads..."
ctest --output-on-failure --test-dir build/release/tests -j"$cpu_count"
RESULT=$?

if [ $RESULT == 0 ]; then
  echo "SUCCESS: All tests passed."
else
  echo "FAIL: Some tests failed."
fi
exit $RESULT