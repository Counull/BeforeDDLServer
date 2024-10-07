//
// Created by lxxr on 9/10/24.
//

#include "RedisConnection.h"
#include <functional>


bool RedisConnection::connect() {
    if (checkContext()) { return true; }; //检测是否已经连接

    context = redisAsyncConnect(config.ip.c_str(), config.port);

    if (!checkContext()) { return false; }

    auto loop = uv_default_loop();
    async.data = this;
    context->data = this;

    uv_async_init(loop, &async, asyncCallback);

    redisLibuvAttach(context, loop);
    redisAsyncSetTimeout(context, (struct timeval) {1, 500000});
    redisAsyncSetConnectCallback(context, &RedisConnection::ConnectCallbackWrapper);
    redisAsyncSetDisconnectCallback(context, &RedisConnection::DisconnectCallbackWrapper);

    return true;
}

bool RedisConnection::checkContext() const noexcept {
    if (!context) {
        std::cout << "Redis context is null" << std::endl;
        return false;
    }
    if (context->err) {
        std::cout << "Redis context error: " << context->errstr << std::endl;
        return false;
    }
    return true;
}

void RedisConnection::ConnectCallbackWrapper(const redisAsyncContext *c, int status) {
    auto thisPtr = static_cast<RedisConnection *>(c->data);
    if (!thisPtr) return;

    thisPtr->authAsync([thisPtr, c, status](auto reply) {
        std::cout << "Auth reply " << reply->str << std::endl;

        if (RedisConnection::ReplyIsOK(reply)) {
            thisPtr->auth = true;
            thisPtr->selectDB(thisPtr->config.dbIndex, [thisPtr, c, status](auto reply) {
                std::cout << "selectDB " << reply->str << std::endl;
            });

            return;
        }
    });


}

void RedisConnection::DisconnectCallbackWrapper(const redisAsyncContext *c, int status) {
    auto thisPtr = static_cast<RedisConnection *>(c->data);
    if (!thisPtr) return;
    thisPtr->disconnectCallback(c, status);

}

void RedisConnection::CmdCallbackWrapper(redisAsyncContext *c, void *r, void *privdata) {
    std::unique_ptr<RedisCommandCallback> callBack(static_cast<RedisCommandCallback*>(privdata));
    if (!callBack) return;
    //很显然这里直接用裸指针回调发生错误会导致内存泄漏
    (*callBack)(static_cast<redisReply *>(r));
    delete callBack;
}


RedisConnection::~RedisConnection() {
    if (checkContext()) {
        redisAsyncFree(context);
    }


    if (context) context->data = nullptr;

    context = nullptr;
}


void RedisConnection::setDisconnectCallback(const RedisConnDisconnectCallback &disconnectCallback) {
    RedisConnection::disconnectCallback = disconnectCallback;
}


void RedisConnection::setConnectCallback(const RedisConnCallback &connectCallback) {
    RedisConnection::connectCallback = connectCallback;
}


void
RedisConnection::setKeyAsync(const std::string_view &key, const std::string_view &val,
                             const RedisCommandCallback &callback, uint ttl) {
    if (!checkContext() || !isAuth()) {
        return;
    }
    int status;
    if (ttl == 0) {
        status = redisAsyncCommand(context, CmdCallbackWrapper, new RedisCommandCallback(callback),
                                   "SET %s %s",
                                   key.data(), val.data());
    } else {
        status = redisAsyncCommand(context, CmdCallbackWrapper, new RedisCommandCallback(callback),
                                   "SETEX %s %u %s",
                                   key.data(), ttl, val.data());
    }


    if (status != REDIS_OK) {
        std::cerr << "Failed to execute redisAsyncCommand: " << context->errstr << std::endl;
    }
}

void RedisConnection::getKeyAsync(const std::string_view &key, const RedisCommandCallback &callback) {

    if (!checkContext() || !isAuth()) {
        return;
    }
    redisAsyncCommand(context, CmdCallbackWrapper, new RedisCommandCallback(callback), "GET %s", key.data());
}

void RedisConnection::setKeyAsyncThreadSafe(const std::string &key, const std::string &val,
                                            const RedisCommandCallback &callback, uint ttl) {

    threadSafeCall([this, key, val, callback, ttl]() {
        setKeyAsync(key, val, callback, ttl);
    });

}

void RedisConnection::getKeyAsyncThreadSafe(const std::string_view &key, const RedisCommandCallback &callback) {
    threadSafeCall([this, key, callback]() {
        getKeyAsync(key, callback);
    });
}


void RedisConnection::threadSafeCall(const std::function<void()> &&func) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.emplace(func);
    }

    uv_async_send(&async);
}


void RedisConnection::authAsync(const RedisCommandCallback &callback) {

    redisAsyncCommand(context, CmdCallbackWrapper, new RedisCommandCallback(callback), "AUTH %s",
                      config.password.c_str());
}

void RedisConnection::selectDB(u_int16_t index, const RedisCommandCallback &callback) {
    redisAsyncCommand(context, CmdCallbackWrapper, new RedisCommandCallback(callback), "SELECT %u",
                      index);
}

void RedisConnection::asyncCallback(uv_async_t *handle) {
    auto *thisPtr = static_cast<RedisConnection *>(handle->data);
    std::queue<std::function<void()>> tasks;
    {
        std::lock_guard<std::mutex> lock(thisPtr->queueMutex);
        std::swap(tasks, thisPtr->taskQueue);
    }

    while (!tasks.empty()) {
        tasks.front()();
        tasks.pop();
    }
}










