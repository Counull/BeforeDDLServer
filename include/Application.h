#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <utility>

#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server.h>

#include "ConfigJsonSerialize.h"
#include "Authority.grpc.pb.h"
#include "AccountServiceImpl.h"
#include "absl/log/initialize.h"
#include "Util.h"
#include "RedisConnection.h"

template<typename T>
concept IsServerConfig = std::is_same_v<std::decay_t<T>, ServerConfig>;

class Application {
public:
    Application() = delete;


    Application(Application &&other) noexcept = default;

    template<IsServerConfig T>
    explicit Application(T &&serverConfig) noexcept:serverConfig(std::forward<T>(serverConfig)) {
        serverAddress = std::format("{}:{}", this->serverConfig.networkConfig.ip,
                                    static_cast<unsigned int>(this->serverConfig.networkConfig.port));

    }

    ~Application();

    int run();


private:
    ServerConfig serverConfig;
    std::string serverAddress;
    std::shared_ptr<RedisConnection> redisConnection;
    std::shared_ptr<grpc::Channel> pChannel;
    std::shared_ptr<grpc::Service> pAccountService;
    std::shared_ptr<grpc::Server> pGrpcServer;


    void createService();

    bool connectToRedis();


};

#endif