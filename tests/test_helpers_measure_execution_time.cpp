#include "test_helpers.hpp"
#include <chrono>
#include <functional>
#include <gtest/gtest.h>
#include <thread>

class MeasureExecutionTimeTest : public ::testing::Test {
public:
  // Setup function that does nothing
  void NoOpSetup(size_t) {}

  // Lambda function that sleeps for a fixed amount of time (10ms)
  void SleepLambda(size_t) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
};

TEST_F(MeasureExecutionTimeTest, MeasuresCorrectAverageTime) {
  size_t input_size = 0; // Not used in NoOpSetup or SleepLambda
  size_t repetitions = 5;
  double measured_time =
      measure_execution_time(std::bind(&MeasureExecutionTimeTest::NoOpSetup,
                                       this, std::placeholders::_1),
                             std::bind(&MeasureExecutionTimeTest::SleepLambda,
                                       this, std::placeholders::_1),
                             input_size, repetitions);

  // Allow some margin for error in timing
  double expected_time_per_call = 0.001; // 10ms in seconds
  double margin_of_error = 0.02;         // 5ms tolerance
  double lower_bound = expected_time_per_call - margin_of_error;
  double upper_bound = expected_time_per_call + margin_of_error;

  EXPECT_GE(measured_time, lower_bound);
  EXPECT_LE(measured_time, upper_bound);
}
