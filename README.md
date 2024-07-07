# Template for Practical Test-Driven Development (TDD) in C++ with CMake

![Build Status](https://github.com/Justin-Randall/tdd-cmake-template/actions/workflows/cmake-multi-platform.yml/badge.svg)

[![codecov](https://codecov.io/github/Justin-Randall/tdd-cmake-template/graph/badge.svg?token=4HYUF98OJ4)](https://codecov.io/github/Justin-Randall/tdd-cmake-template)

This is primarily a personal repository used when starting new C++ projects. A bit of a "cut-and-waste" template where I can simply change the project name in the root, rename the `tests/test_<project_name>.cpp` file and have a pleasant start to tackle code with a TDD approach.

From time to time, as I find goodies that are missing, I will bring them back to this repository. Feel free to submit a PR if something generally useful is missing or a bug is uncovered (or even cleaning up the CMakeLists.txt files).

## Usage

Easist way: grab [the compressed archive](https://github.com/Justin-Randall/tdd-cmake-template/archive/refs/heads/master.zip) from GitHub. Unzip it into a new project folder of your choice.

There are two variables used in the `tests/` subdirectory. One is inherited from the top-level `CMakeLists.txt`:

```cmake
...

project(tdd_template LANGUAGES CXX)
```

Simply change `tdd_template` to whatever the new project name is.

There is another variable in `tests/CMakeLists.txt`:

```cmake
# ###############################################
# Configuration Variables
#
# Set this to whatever the best coverage report
# has produced. Recommend to always INCREASE it
# because BETTER is BETTER and 100 is BEST.
# Defaults to 100 since this template should
# always have 100% coverage before committing to
# source control.
set(TEST_COVERAGE_THRESHOLD 100)

# End Configuration Variables
# ###############################################
```

It is self-explanatory.

If this template is being applied for an EXISTING project that does not have a tests subdirectory yet, be sure to update the project-root's `CMakeLists.txt` with:

```cmake
add_subdirectory(tests)
```

and definitely dial `TEST_COVERAGE_THRESHOLD` down.

If your development environment includes lcov or OpenCppCoverage, that threshold will be checked and if coverage is below it, the build will fail. Be sure to run the "coverage" target in the IDE before committing to source control.

## GoogleTest and Coverage

CMake will detect the platform and whether or not gcovr/lcov/genhtml are present. For Windows, it will check for OpenCppCoverage.exe. Since this is hosted on GitHub, there is also a workflow that will install necessary coverage tools and generate coverage reports. It DOES use [CodeCov.io](https://codecov.io). For single dev accounts, it is free to use. Some of the ShieldIO workflows that I used to leverage stopped working sometime in the last couple of months.

## Custom time complexity testing

There are some additional headers and sources included here that can be commented out in `project_root/tests/CMakeLists.txt` that may be of use to ensure the time complexity in Big-O notation for your code remains as expected as future changes are made. Nobody wants an O(1) method to become O(n^2) unexpectedly and require a bunch of profiling sessions to track down. This makes it easier to let the test suite catch these issues. They should be FAST (on the order of milliseconds), but you will need to supply enough sample runs to ensure provably accurate results over 99% of the time. This is one of those rare occassions that a rare and random false failure is preferable to no coverage.
