//
// Created by lxxr on 9/10/24.
//

#ifndef BEFOREDDLSERVER_REDISCONNECTION_H
#define BEFOREDDLSERVER_REDISCONNECTION_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <uv.h>
#include <adapters/libuv.h>
#include <hiredis.h>
#include <async.h>

#include "Config.h"

using RedisConnCallback = std::function<redisConnectCallback>;
using RedisConnDisconnectCallback = std::function<redisDisconnectCallback>;
using RedisCommandCallback = std::function<void(redisReply *)>;
template<typename T>
concept RedisConfigType = std::is_same_v<std::decay_t<T>, RedisConfig>;


class RedisConnection {
public:
    template<RedisConfigType RCT>
    explicit RedisConnection(RCT &&config): config(std::forward<RedisConfig>(config)) {
    }

    ~RedisConnection();

    bool connect();

    bool checkContext() const noexcept;


    void setKeyAsync(const std::string_view &key, const std::string_view &val, const RedisCommandCallback &callback);

    void GetKeyAsync(const std::string_view &key, const RedisCommandCallback &callback);


    void setDisconnectCallback(const RedisConnDisconnectCallback &disconnectCallback);

    void setConnectCallback(const RedisConnCallback &connectCallback);

    static inline bool ReplyIsOK(redisReply *reply) noexcept {
        return reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0;
    }


private:

    RedisConfig config;
    redisAsyncContext *context{};
    RedisConnCallback connectCallback;
    RedisConnDisconnectCallback disconnectCallback;
    bool auth = false;
public:
    bool isAuth() const;

private:
    void AuthAsync(const RedisCommandCallback &callback);


    static void ConnectCallbackWrapper(const redisAsyncContext *c, int status);

    static void DisconnectCallbackWrapper(const redisAsyncContext *c, int status);

    static void CallbackWrapper(redisAsyncContext *c, void *r, void *privdata);

};


#endif //BEFOREDDLSERVER_REDISCONNECTION_H
