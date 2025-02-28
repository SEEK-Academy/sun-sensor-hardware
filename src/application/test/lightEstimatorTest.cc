#include <array>
#include <span>

#include <gtest/gtest.h>
#include "DSP/lightEstimator.h"
#include "datatypes.h"

class LightEstimatorTests : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  LightEstimatorTests() {
     // You can do set-up work for each test here.
  }

  ~LightEstimatorTests() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

TEST_F(LightEstimatorTests, EstimateRotation) {
  std::array <float,4> measurements = {1.0,0.0,0.0,0.0};
  math::Vector3 angleEstimate = LightEstimator::estimateRotationX(std::span(measurements));
}
