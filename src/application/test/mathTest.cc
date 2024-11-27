#include <array>
#include <span>

#include <gtest/gtest.h>
#include "math_functions/avg.h"

class MathTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  MathTest() {
     // You can do set-up work for each test here.
  }

  ~MathTest() override {
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

TEST_F(MathTest, EstimatePlane) {
  std::array <float,4> measurements = {1.3712f,1.0f};
  float angleEstimate = math::rootMeanSquare<float,std::array <float,4>>(measurements);
  ASSERT_FLOAT_EQ(angleEstimate, 1.2f);
  
}
