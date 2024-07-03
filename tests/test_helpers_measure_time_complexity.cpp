#include "test_helpers.hpp"
#include <gtest/gtest.h>


class MeasureTimeComplexityTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup code if needed
  }

  void TearDown() override {
    // Teardown code if needed
  }
};

// Test case for constant time complexity O(1)
TEST_F(MeasureTimeComplexityTest, ConstantTimeComplexity) {
  auto setup = [](size_t input_size) {};
  auto lambda = [](size_t input_size) { return; };

  std::vector<size_t> input_sizes = {100, 200, 300, 400, 500};
  Complexity complexity = measure_time_complexity(setup, lambda, input_sizes);

  EXPECT_EQ(complexity, Complexity::O1);
}

// Test case for logarithmic time complexity O(log n)
TEST_F(MeasureTimeComplexityTest, LogarithmicTimeComplexity) {
  auto setup = [](size_t input_size) {};
  auto lambda = [](size_t input_size) {
    for (size_t i = 1; i < input_size; i *= 2) {
    }
  };

  std::vector<size_t> input_sizes = {100, 200, 400, 800, 1600};
  Complexity complexity = measure_time_complexity(setup, lambda, input_sizes);

  EXPECT_EQ(complexity, Complexity::OLogN);
}

// Test case for linear time complexity O(n)
TEST_F(MeasureTimeComplexityTest, LinearTimeComplexity) {
  auto setup = [](size_t input_size) {};
  auto lambda = [](size_t input_size) {
    for (size_t i = 0; i < input_size; ++i) {
    }
  };

  std::vector<size_t> input_sizes = {100, 200, 300, 400, 500};
  Complexity complexity = measure_time_complexity(setup, lambda, input_sizes);

  EXPECT_EQ(complexity, Complexity::ON);
}

// Test case for quadratic time complexity O(n^2)
TEST_F(MeasureTimeComplexityTest, QuadraticTimeComplexity) {
  auto setup = [](size_t input_size) {};
  auto lambda = [](size_t input_size) {
    for (size_t i = 0; i < input_size; ++i) {
      for (size_t j = 0; j < input_size; ++j) {
      }
    }
  };

  std::vector<size_t> input_sizes = {10, 20, 30, 40, 50};
  Complexity complexity = measure_time_complexity(setup, lambda, input_sizes);

  EXPECT_EQ(complexity, Complexity::ON2);
}

// Test case for cubic time complexity O(n^3)
TEST_F(MeasureTimeComplexityTest, CubicTimeComplexity) {
  auto setup = [](size_t input_size) {};
  auto lambda = [](size_t input_size) {
    for (size_t i = 0; i < input_size; ++i) {
      for (size_t j = 0; j < input_size; ++j) {
        for (size_t k = 0; k < input_size; ++k) {
        }
      }
    }
  };

  std::vector<size_t> input_sizes = {10, 20, 30, 40, 50};
  Complexity complexity = measure_time_complexity(setup, lambda, input_sizes);

  EXPECT_EQ(complexity, Complexity::ON3);
}
