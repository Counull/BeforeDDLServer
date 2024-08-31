//
// Created by lxxr on 8/30/24.
//

#ifndef BEFOREDDLSERVER_CONFIG_H
#define BEFOREDDLSERVER_CONFIG_H

#include <string>
#include <string_view>

class NetworkConfig {
public:
    std::string_view ip;
    u_int16_t port;

    //为json序列化提供默认值
    NetworkConfig() : ip("0.0.0.0"), port(50051) {}

    NetworkConfig(const std::string_view &ip, int port)
            : ip(ip), port(port) {}

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const NetworkConfig &rhs) const = default;

};

class TencentApiConfig {
public:
    std::string_view secretId;
    std::string_view secretKey;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const TencentApiConfig &rhs) const = default;

};


class ServerConfig {
public:
    NetworkConfig networkConfig;
    TencentApiConfig tencentApiConfig;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const ServerConfig &rhs) const = default;


};

#endif //BEFOREDDLSERVER_CONFIG_H
