#include "Application.h"

#include <utility>

#include "absl/flags/flag.h"

Application::~Application() = default;


int Application::run() {
    absl::InitializeLog();
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    uv_loop_t *loop = uv_default_loop();

    // Initialize the loop
    if (uv_loop_init(loop) != 0) {
        std::cerr << "Failed to initialize libuv loop" << std::endl;
        return false;
    }
    
    if (connectToRedis()) {
        std::cout << "Connected to redis" << std::endl;
    }
    createService();
    uv_run(loop, UV_RUN_DEFAULT);
    pGrpcServer->Shutdown();

    uv_loop_close(loop);
    return 0;
}

void Application::createService() {

    pAccountService = std::make_shared<AccountServiceImpl>(serverConfig.aliApiConfig, serverConfig.smsConfig,
                                                           pRedisConnection);
    grpc::SslServerCredentialsOptions sslOpts;
    auto privateKey = Util::ReadFile(serverConfig.sslConfig.keyPath);
    auto certificate = Util::ReadFile(serverConfig.sslConfig.certPath);
    sslOpts.pem_key_cert_pairs = {{std::move(privateKey), std::move(certificate)}};

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::SslServerCredentials(sslOpts));
    builder.RegisterService(pAccountService.get());

    pGrpcServer = builder.BuildAndStart();
    std::cout << "Server listening on " << serverAddress << std::endl;

}

bool Application::connectToRedis() {

    pRedisConnection = std::make_shared<RedisConnection>(this->serverConfig.redisConfig);

    pRedisConnection->setConnectCallback([](auto context, auto status) {
        std::cout << "Call bake in application" << " redis connected" << std::endl;

    });
    pRedisConnection->setDisconnectCallback([](auto context, auto status) {
        std::cout << "Call bake in application" << " redis disconnect" << std::endl;
    });


    if (!pRedisConnection->connect()) {
        std::cerr << "Failed to connect to redis" << std::endl;
        return false;
    }


    return true;

}









