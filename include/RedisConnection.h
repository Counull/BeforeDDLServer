//
// Created by lxxr on 9/10/24.
//

#ifndef BEFOREDDLSERVER_REDISCONNECTION_H
#define BEFOREDDLSERVER_REDISCONNECTION_H

#include <string>
#include "Config.h"

template<typename T>
concept RedisConfigType = std::is_same_v<std::decay_t<T>, RedisConfig>;


class RedisConnection {
    template<RedisConfigType RCT>
    explicit RedisConnection(RCT &&config) {

    }


};


#endif //BEFOREDDLSERVER_REDISCONNECTION_H
