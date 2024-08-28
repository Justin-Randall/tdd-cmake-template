# Template for Practical Test-Driven Development (TDD) in C++ with CMake

![Build Status](https://github.com/Justin-Randall/tdd-cmake-template/actions/workflows/cmake-multi-platform.yml/badge.svg)

[![codecov](https://codecov.io/github/Justin-Randall/tdd-cmake-template/graph/badge.svg?token=4HYUF98OJ4)](https://codecov.io/github/Justin-Randall/tdd-cmake-template)

Saves the hassle of:

- Setting up pre-commit hooks to ensure code builds, passes tests and meets coverage thresholds
- Writing `./CMakeLists.txt` to add `./tests/`
- Writing `./tests/CMakeLists.txt` to get prerequisites
  - Google Test
  - Check for coverage binaries like [`lcov`](https://github.com/linux-test-project/lcov) or [`OpenCppCoverage`](https://github.com/OpenCppCoverage/OpenCppCoverage)
- Setting up a baseline TDD starting point
- Generating coverage reports
- Setting minimum coverage thresholds for passing builds
- Getting the GitHub Actions/Workflows for CI builds up and running
- Setting up build status and code coverage badges

This is a template where simply changing the project name in the root, renaming the `tests/test_<project_name>.cpp` file leads to a pleasant start to tackle code with a TDD approach.

## Usage

Easiest way: grab [the compressed archive](https://github.com/Justin-Randall/tdd-cmake-template/archive/refs/heads/master.zip) from GitHub. Unzip it into a new project folder of your choice.

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

If this template is being applied for an EXISTING project that does not have a tests subdirectory yet, be sure to update the project-root's `CMakeLists.txt` with:

```cmake
add_subdirectory(tests)
```

and definitely dial `TEST_COVERAGE_THRESHOLD` down.

If the local development environment includes [lcov](https://github.com/linux-test-project/lcov) or [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage), that threshold will be checked and if coverage is below it, the build will fail. Always run the "coverage" target in the IDE before committing to source control.

## GoogleTest and Coverage

CMake will detect the platform and whether or not [gcovr](https://github.com/gcovr/gcovr)/[lcov](https://github.com/linux-test-project/lcov)/genhtml are present. For Windows, it will check for [OpenCppCoverage.exe](https://github.com/OpenCppCoverage/OpenCppCoverage). Since this is hosted on GitHub, there is also a workflow that will install necessary coverage tools and generate coverage reports. It DOES use [CodeCov.io](https://codecov.io). For single dev accounts, it is free to use. Some of the ShieldIO workflows that I used to leverage stopped working sometime in the last couple of months.

The build system assumes coverage tools are administratively installed. Since the tools are also available on GitHub, this may change in the future to download, build and use the locally built-versions.

If the build complains when running coverage, ensure lcov-2.0 or above are installed. In March of 2023, a major revision was released that adds new command line options that MUST be present, but als break earlier (1.x) versions of lcov and the generators it invokes.

## Custom time complexity testing

There are some additional headers and sources included here that can be commented out in `project_root/tests/CMakeLists.txt` that may be of use to ensure the time complexity in Big-O notation for your code remains as expected as future changes are made. Nobody wants an O(1) method to become O(n^2) unexpectedly and require a bunch of profiling sessions to track down. This makes it easier to let the test suite catch these issues. They should be FAST (on the order of milliseconds), but you will need to supply enough sample runs to ensure provably accurate results over 99% of the time. This is one of those rare occasions that a rare and random false failure is preferable to no coverage.

## Source control workflow

In `scripts/source_control/githooks` is a precommit script that checks that code builds, tests pass, and coverage meets a minumum threshold. This automates away the manual processes that are prone to someone forgetting one step in a growing list of things they need on a check-list before committing changes. It is currently git-oriented. It can be refactored to also handle other source control systems that allow pre-commit checks like perforce (Helix-Core client extensions in Lua, for example).
