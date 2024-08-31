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
    NetworkConfig networkConfig{"10.31.7.7", 8888};
    //这里是string_view的话需要调用parse函数而不是隐式转换
    auto j = nlohmann::json::parse(jsonStr);
    auto deserialize = j.template get<NetworkConfig>();
    ASSERT_EQ(networkConfig, deserialize);
    j = networkConfig;
    ASSERT_STREQ(j.dump().c_str(), jsonStr.data());

    jsonStr = R"(
{
  "networkConfig": {
    "ip": "23.114.156.233",
    "port": 451
  },
  "tencentApiConfig": {
    "secretId": "LSQ47C3424Vczx",
    "secretKey": "YSY7cbbDD2313"
  }
}
)";
    j = nlohmann::json::parse(jsonStr);
    auto serverConfig = j.template get<ServerConfig>();
    ASSERT_STREQ(serverConfig.networkConfig.ip.data(), "23.114.156.233");
    ASSERT_EQ(serverConfig.networkConfig.port, 451);
    ASSERT_STREQ(serverConfig.tencentApiConfig.secretId.data(), "LSQ47C3424Vczx");
    ASSERT_STREQ(serverConfig.tencentApiConfig.secretKey.data(), "YSY7cbbDD2313");
}