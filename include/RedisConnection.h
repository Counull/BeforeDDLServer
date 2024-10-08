//
// Created by lxxr on 9/10/24.
//

#ifndef BEFOREDDLSERVER_REDISCONNECTION_H
#define BEFOREDDLSERVER_REDISCONNECTION_H

#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <uv.h>
#include <adapters/libuv.h>
#include <hiredis.h>
#include <async.h>
#include <thread>
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

    void setKeyAsyncThreadSafe(const std::string &key, const std::string &val, const RedisCommandCallback &callback,
                               uint ttl = 0);

    void getKeyAsyncThreadSafe(const std::string_view &key, const RedisCommandCallback &callback);

    void threadSafeCall(const std::function<void()> &&func);

    void setKeyAsync(const std::string_view &key, const std::string_view &val, const RedisCommandCallback &callback,
                     uint ttl = 0);

    void getKeyAsync(const std::string_view &key, const RedisCommandCallback &callback);


    void setDisconnectCallback(const RedisConnDisconnectCallback &disconnectCallback);

    void setConnectCallback(const RedisConnCallback &connectCallback);

    void selectDB(u_int16_t index, const RedisCommandCallback &callback);

    static inline bool ReplyIsOK(redisReply *reply) noexcept {
        return reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0;
    }

    inline bool isAuth() const { return auth; };
private:

    RedisConfig config;
    redisAsyncContext *context{};
    RedisConnCallback connectCallback;
    RedisConnDisconnectCallback disconnectCallback;
    uv_async_t async;
    std::mutex queueMutex;
    std::queue<std::function<void()>> taskQueue;
    bool auth = false;


private:
    void authAsync(const RedisCommandCallback &callback);


    static void ConnectCallbackWrapper(const redisAsyncContext *c, int status);

    static void DisconnectCallbackWrapper(const redisAsyncContext *c, int status);

    static void CmdCallbackWrapper(redisAsyncContext *c, void *r, void *privdata);

    static void asyncCallback(uv_async_t *handle);

};


#endif //BEFOREDDLSERVER_REDISCONNECTION_H
