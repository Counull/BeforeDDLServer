#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <utility>

#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>

#include "ConfigJsonSerialize.h"
#include "Authority.grpc.pb.h"

class Application {
public:
    Application() = delete;

    explicit Application(ServerConfig serverConfig) : serverConfig(std::move(serverConfig)) {
        serverAddress = std::move(
                this->serverConfig.networkConfig.ip + ":" + std::to_string(this->serverConfig.networkConfig.port));
    };

    ~Application();

    int run();

private:

    ServerConfig serverConfig;
    std::string serverAddress;
    std::shared_ptr<grpc::Channel> pChannel;
    std::unique_ptr<grpc::Server> pAccountService;

    void createChannel();

    void createService();


};

#endif