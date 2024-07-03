# Practical Test-Driven Development (TDD) in C++ with CMake

I am going to break from some of the eclectic bag of tricks to talk about making a (hopefully) helpful template for creating a TDD template for C++ code using [CMake](https://cmake.org/) and [Google Test](https://github.com/google/googletest). Yes, I know, it's like discussing the joy of flossing, but bear with me. CMake, its built-in test targets and even dependency management is now as mature as a fine wine (or not so fine cheese).

## TDD Fundamentals (Review)

For those unfamiliar with test-driven development, the flow is: you write a test first, even before writing a single header file or any code implementing functionality. The code first "pretends" to be what you think a programmer will write if they use your work. So there is no main program or library to link or anything else. The very first thing to write is the test.

There is plenty of great literature on why this really helps focus work and thought on what it is you want to build, but let's assume you are a fan of TDD, but in C++. It is a an exercise in more re-search (hahah, pardon the pun) to set it up each time.

## Initial Setup

It is nice to have the simplest of TDD projects to use as a cut-and-waste starting point. For CMake-based projects, it is pretty much:

```shell
project_root/
    CMakeLists.txt
    tests/
        CMakeLists.txt
        test_project_name.cpp
```

It is mostly that simple. A few caveats: if you are in visual studio code, after creating the files, restart VSCode or re-open the folder so it catches that it is a CMake project and then be sure to select a kit for your platform (clang, MSVC, etc.).

For the purposes of this article, I am going to use Google Test, which CTest is fine with, and so are a lot of tools that plug in in nicely with IDEs.

## project_root

Let's start with CMakeLists.txt. You can cut and paste this and we will have a look at it line-by-line.

```scss
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

project(tdd_template LANGUAGES CXX)

# setup testing
include(CTest)
enable_testing()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

include(FetchContent)

include_directories("${gtest_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(tests)

```

This is the only file you really need in the root of the project folder. It sets up the project, the C++ standard, and the testing. It also includes the tests folder, which is where the tests will be written.

Let's break it down line by line:

```scss
cmake_minimum_required(VERSION 3.11)
```

This version should be bumped when utilizing CMake features or when CMake warns about deprecating. When deprecating, fix the old directives, bump the version and test it.

```scss
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

project(tdd_template LANGUAGES CXX)
```

This may seem pedantic, and perhaps it is. If the code/library you are writing targets older standards, then by all means adjust as needed. I *highly* recommend warnings as errors and try to either provide up-stream fixes if your dependencies generate warnings, or selectively disable them for 3rd party code and be very suspect of it.

Lastly, the project name is what you will likely be changing when cutting and pasting. Otherwise this CMakeLists.txt is fine.

```scss
# setup testing
include(CTest)
enable_testing()
```

This is kind of self-explanatory. It will provide some handy test targets.

```scss
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()
```

This is mostly a personal preference to let IDEs display sources conveniently.

```scss
include(FetchContent)

include_directories("${gtest_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(tests)
```

The testing magick is here. FetchContent is super-helpful. This will let you grab Google Test at version you specify in tests/CMakeLists.txt. CMake defines as well as required include directories are available from this point. Your top-level project is ready to run tests from the `tests` subdirectory, but that directory needs a couple of files before it is ready to go.

## project_root/tests

The project_root/CMakeLists.txt had `add_subdirectory(tests)`, so if the subdir does not exist and does not have a CMakeLists.txt, the build will fail before even creating makefiles or project files. There are two important files here: `CMakeLists.txt` and the source file for the test template. One other customation you need to make is using the project name for the source file. Since the project name here is `tdd_template`, then `test_tdd_template.cpp` will be the source file name (as we shall see from the `project_root/CMakeLists.txt` file we are about to create).

Here is `project_root/tests/CMakeLists.txt`:

```scss
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # release-1.14.0
)
FetchContent_MakeAvailable(googletest)

set(UNIT_TEST ${PROJECT_NAME}_tests)

add_executable(${UNIT_TEST} "test_${PROJECT_NAME}.cpp")

target_compile_features(${UNIT_TEST} PRIVATE cxx_std_20)

target_link_libraries(${UNIT_TEST} PRIVATE gtest_main)

add_test(NAME ${UNIT_TEST} COMMAND ${UNIT_TEST})

include_directories("${gtest_SOURCE_DIR}/include")

set(TEST_COMMAND_LINE_OPTIONS ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures)

```

Lastly, the test program needs to be built from test program sources. `tests/CMakeLists.txt` says that the unit test is built from source files, and the only source file so far is `test_${PROJECT_NAME}.cpp`. `PROJECT_NAME` is defined as `tdd_template` so the source file is `test_tdd_template.cpp`.

Since the core of TDD is that the test should FAIL until functionality is implemented, let's write `test_tdd_template.cpp` such that it compiles, but fails right away. From this point, you can start to implement your tests and are ready to roll with C++ test-drivent development using CMake:

### project_root/tests/test_tdd_template.cpp

```cpp
#include "gtest/gtest.h"

TEST(TDDTemplate, test1) { EXPECT_EQ(1, 0); }
```

## Conclusion

This is now a project with a test framework that could become a header-only distribution, a compiled and linked library or a standalone program.

For Visual Studio Code users, I do recommend adding a launch.json target to debug the test. Whether it is gdb (linux), cppvsdebug (MSVC on Windows) or others, the launch program for the target is this line:

```json
            "program": "${workspaceFolder}/build/tests/Debug/tdd_template_tests.exe", # .exe for windows devs
```

Where "tdd_template" is replaced with your project name.

How you integrate the generated project files with your favorite IDE is beyond the scope of this exercise.

If you give this a shot and find some problems, feel free to comment. I have tested it in my own environments and use it as a "cut-and-waste" starting point for new work.

Adapting a test framework to existing code, especially with an eye to attempt TDD, is going to be like pushing mud up a mountain. TDD is something to *START* with, not slap on top of a bowl of spaghetti and call it untangled.

## Postscript

There are some other great tools that can be plugged into this framework. Test coverage tracking with OpenCPPCoverage is a reasonably portable way to track how much functional code is covered by tests (it should be 100%). IDEs can read its output to show, in the editor, which lines have not had test coverage (coverage gutters in VSCode, for example).

The most important goal is to have a nice launchpad template to start TDD without having to recreate it from scratch every time.

### Custom time complexity testing

There are some additional headers and sources included here that are commented out in `project_root/tests/CMakeLists.txt` that may be of use to ensure the time complexity in Big-O notation for your code remains as expected as future changes are made. Nobody wants an O(1) method to become O(n^2) unexpectedly and require a bunch of profiling sessions to track down. This makes it easier to let the test suite catch these issues. They should be FAST (on the order of milliseconds), but you will need to supply enough sample runs to ensure provably accurate results over 99% of the time. This is one of those rare occassions that a rare and random false failure is preferable to no coverage.
