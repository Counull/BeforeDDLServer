//
// Created by lxxr on 8/30/24.
//

#ifndef BEFOREDDLSERVER_NETWORKCONFIG_H
#define BEFOREDDLSERVER_NETWORKCONFIG_H


#include <nlohmann/json.hpp>
#include "Config.h"
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(NetworkConfig, ip, port)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TencentApiConfig, SecretId, SecretKey)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ServerConfig, networkConfig, tencentApiConfig)
#endif //BEFOREDDLSERVER_NETWORKCONFIG_H
