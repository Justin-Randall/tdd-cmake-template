cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

project(tdd_template LANGUAGES CXX)

# Ensure Source control hooks are configured
# (just git for now)
add_custom_target(LocalGitConfiguration ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Configuring Git Hooks"

    # Using --local ensures this applies to this repository only
    COMMAND git config --local core.hooksPath ${CMAKE_SOURCE_DIR}/scripts/source_control/githooks
)

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
