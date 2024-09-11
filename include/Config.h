//
// Created by lxxr on 8/30/24.
//

#ifndef BEFOREDDLSERVER_CONFIG_H
#define BEFOREDDLSERVER_CONFIG_H

#include <string>
#include <string_view>
#include <utility>

/// 这个头文件其实并不让我自己满意，因为
/// 1.这些的配置类的成员变量都是public的，只是暂时这样比较方便
/// 2.一些基础组件会依赖这些类进行构建，而这些基础组件会include这个被频繁修改的头文件且会造成依赖混乱
/// 其实他们应该是一个独立的类，而不是一个类的集合，这样会更加清晰
/// 但是使用的一些库导致了这样的设计，而彻底完美的实现需要更多更复杂的代码，比如使用友元并重构一些代码
class NetworkConfig {
public:
    std::string ip;
    u_int16_t port;

    //为json序列化提供默认值
    NetworkConfig() : ip("0.0.0.0"), port(50051) {}

    NetworkConfig(std::string ip, int port)
            : ip(std::move(ip)), port(port) {}

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const NetworkConfig &rhs) const = default;
};

class TencentApiConfig {
public:
    std::string secretId;
    std::string secretKey;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const TencentApiConfig &rhs) const = default;
};

class AliApiConfig {
public:
    std::string accessKeyId;
    std::string accessKeySecret;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const AliApiConfig &rhs) const = default;
};


class SMSConfig {
public:
    std::string signName;
    std::string templateCode;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const SMSConfig &rhs) const = default;
};

class SSLConfig {
public:
    std::string certPath;
    std::string keyPath;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const SSLConfig &rhs) const = default;
};

class RedisConfig {
public:
    std::string ip;
    u_int16_t port;
    std::string password;

    RedisConfig() : ip("localhost"), port(6379) {
    }

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const RedisConfig &rhs) const = default;
};

class ServerConfig {
public:
    NetworkConfig networkConfig;
    TencentApiConfig tencentApiConfig;
    AliApiConfig aliApiConfig;
    SMSConfig smsConfig;
    SSLConfig sslConfig;
    RedisConfig redisConfig;

    //为了方便测试，必须显示声明==运算符为default
    bool operator==(const ServerConfig &rhs) const = default;


};


#endif //BEFOREDDLSERVER_CONFIG_H
