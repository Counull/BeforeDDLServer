//
// Created by lxxr on 8/30/24.
//

#ifndef BEFOREDDLSERVER_NETWORKCONFIG_H
#define BEFOREDDLSERVER_NETWORKCONFIG_H


#include <nlohmann/json.hpp>
#include "Config.h"


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(NetworkConfig, ip, port)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TencentApiConfig, secretId, secretKey)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(AliApiConfig, accessKeyId, accessKeySecret)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SMSConfig, signName, templateCode)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SSLConfig, certPath, keyPath)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(RedisConfig, ip, port, password, dbIndex)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(ServerConfig, networkConfig, tencentApiConfig, aliApiConfig, smsConfig,
                                                sslConfig, redisConfig)

#endif //BEFOREDDLSERVER_NETWORKCONFIG_H
