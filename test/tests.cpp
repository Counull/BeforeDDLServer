#include <gtest/gtest.h>
#include "Application.h"
#include "ConfigJsonSerialize.h"

TEST(SampleTest, AssertionTrue) {



//    ASSERT_TRUE(application.run(<#initializer#>) == 0);
}

/// Test for serialization
TEST(SerilaizationTest, JsonConfig) {
    //使用string_view要小心，因为string_view不会拷贝字符串，所以需要保证字符串的生命周期
    //最好不要像我这样脱离string单独使用string_view，如果此处将jsonStr传递到函数外超过函数生命，
    //那么jsonStr将会被销毁，string_view将会指向一个无效的字符串
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