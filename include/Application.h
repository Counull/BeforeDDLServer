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

template<typename T>
concept IsServerConfig = std::is_same_v<std::decay_t<T>, ServerConfig>;

class Application {
public:
    Application() = delete;


    Application(Application &&other) noexcept = default;

    template<IsServerConfig T>
    explicit Application(T &&serverConfig) noexcept;

    ~Application();

    int run();

private:

    ServerConfig serverConfig;
    std::string serverAddress;
    std::shared_ptr<grpc::Channel> pChannel;
    std::unique_ptr<grpc::Server> pAccountService;
    std::unique_ptr<grpc::Server> pHelloService;


    void createService();


};

#endif