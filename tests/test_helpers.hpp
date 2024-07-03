#ifndef _INCLUDED_test_helpers_hpp
#define _INCLUDED_test_helpers_hpp
#include "gtest/gtest.h"
#include <vector>

/**
 * @brief
 * Order of complexity (Big O notation), from fastest to slowest.
 */
enum class Complexity {
  ERROR,       // Calculation failed or complexity cannot be determined
  O1,          // O(1) - Constant time
  OLogN,       // O(log n) - Logarithmic time
  ON,          // O(n) - Linear time
  ONLogN,      // O(n log n) - Linearithmic time
  ON2,         // O(n^2) - Quadratic time
  ON3,         // O(n^3) - Cubic time
  O2N,         // O(2^n) - Exponential time
  ONFactorial, // O(n!) - Factorial time
  OUnknown     // Complexity is not classified in the above categories
};

/**
 * @brief Helper function to convert Complexity enum to string.
 *
 * @param complexity
 * @return std::string
 */
std::string to_string(Complexity complexity);

double measure_execution_time(const std::function<void(size_t)> &setup,
                              const std::function<void(size_t)> &lambda,
                              size_t input_size, size_t repetitions);

Complexity determine_complexity(const std::vector<size_t> &input_sizes,
                                const std::vector<double> &times);
/**
 * @brief Measure the asymptotic time complexity of a function.
 *
 * @param setup
 * A setup function that prepares the input for the lambda function. The setup
 * function should take a single size_t for input size.
 *
 * @param lambda
 * The lambda function to measure. The lambda function should take a single
 * size_t for input size.
 *
 * @param input_sizes
 * A vector of input sizes to test.
 *
 * @param repetitions
 * The number of times to repeat the lambda function for each input size.
 *
 * @return ComplexityThreshold
 */
Complexity
measure_time_complexity(const std::function<void(size_t input_size)> &setup,
                        const std::function<void(size_t input_size)> &lambda,
                        const std::vector<size_t> &input_sizes,
                        size_t repetitions = 10);

#endif // _INCLUDED_test_helpers_hpp
