#include <gtest/gtest.h>
#include "Application.h"
#include "ConfigJsonSerialize.h"

TEST(SampleTest, AssertionTrue) {

    Application application;

//    ASSERT_TRUE(application.run(<#initializer#>) == 0);
}

/// Test for serialization
TEST(SerilaizationTest, JsonConfig) {
    std::string_view jsonStr = R"({"ip":"10.31.7.7","port":8888})";
    NetworkConfig networkConfig = {"10.31.7.7", 8888};
    nlohmann::json j = nlohmann::json::parse(jsonStr);
    NetworkConfig deserialize = j.template get<NetworkConfig>();
    ASSERT_EQ(networkConfig, deserialize);
    j = networkConfig;
    ASSERT_STREQ(j.dump().c_str(), jsonStr.data());
}