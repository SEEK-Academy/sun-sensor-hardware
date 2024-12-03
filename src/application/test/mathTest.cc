#include <array>
#include <span>

#include <gtest/gtest.h>
#include "math_functions/avg.h"

class MathTest : public testing::Test
{
  protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    MathTest()
    {
        // You can do set-up work for each test here.
    }

    ~MathTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

TEST_F(MathTest, testRMS)
{
    std::array<float, 2> measurements  = {1.0f, 1.192f};
    float                avg = math::rootMeanSquare(std::span(measurements));
    EXPECT_NEAR(avg, 1.100196346f, 0.0001);
}

TEST_F(MathTest, testWeightedRange)
{
    std::array<float, 4> measurements = {0.1f, 0.2f, 1.0f, 0.2f};
    std::array<float, 4> weights = {-60.0f, -30.0f, 30.0f, 60.0f};
    float angleEstimate = math::weightedRange(std::span(measurements),std::span(weights));
    EXPECT_NEAR(angleEstimate, 30.0f, 2.0f);
}