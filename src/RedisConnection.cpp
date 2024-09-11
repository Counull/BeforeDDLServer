//
// Created by lxxr on 9/10/24.
//

#include "RedisConnection.h"
#include <functional>


bool RedisConnection::connect() {
    if (checkContext()) { return true; };


    context = redisAsyncConnect(config.ip.c_str(), config.port);
    if (!checkContext()) { return false; }

    context->data = this;
    redisLibuvAttach(context, uv_default_loop());
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
    thisPtr->AuthAsync([thisPtr, c, status](auto reply) {
        std::cout << "Auth reply " << reply->str << std::endl;
        if (RedisConnection::ReplyIsOK(reply)) {
            thisPtr->auth = true;
            thisPtr->connectCallback(c, status);
            return;
        }
    });


}

void RedisConnection::DisconnectCallbackWrapper(const redisAsyncContext *c, int status) {
    auto thisPtr = static_cast<RedisConnection *>(c->data);
    if (!thisPtr) return;
    thisPtr->disconnectCallback(c, status);

}

void RedisConnection::CallbackWrapper(redisAsyncContext *c, void *r, void *privdata) {
    std::cout << __FUNCTION__ << std::endl;
    auto callBack = static_cast<RedisCommandCallback *>(privdata);
    if (!callBack) return;
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
                             const RedisCommandCallback &callback) {
    if (!checkContext() || !isAuth()) {
        return;
    }
    redisAsyncCommand(context, CallbackWrapper, new RedisCommandCallback(callback), "SET %s %s", key.data(),
                      val.data());
}

void RedisConnection::GetKeyAsync(const std::string_view &key, const RedisCommandCallback &callback) {
    if (!checkContext() || !isAuth()) {
        return;
    }
    redisAsyncCommand(context, CallbackWrapper, new RedisCommandCallback(callback), "GET %s", key.data());
}

void RedisConnection::AuthAsync(const RedisCommandCallback &callback) {
    redisAsyncCommand(context, CallbackWrapper, new RedisCommandCallback(callback), "AUTH %s",
                      config.password.c_str());
}

bool RedisConnection::isAuth() const {
    return auth;
}







