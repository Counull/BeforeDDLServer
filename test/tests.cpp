#include <gtest/gtest.h>
#include "Application.h"

TEST(SampleTest, AssertionTrue) {

    Application application;

    ASSERT_TRUE(application.run() == 0);
}