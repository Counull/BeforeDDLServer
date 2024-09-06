#include "Application.h"

#include <utility>

#include "absl/flags/flag.h"

Application::~Application() = default;


int Application::run() {
    absl::InitializeLog();
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    createService();
    return 0;
}

void Application::createService() {
    pAccountService = std::make_shared<AccountServiceImpl>(serverConfig.aliApiConfig, serverConfig.smsConfig);


    grpc::SslServerCredentialsOptions sslOpts;
    std::string privateKey = Util::ReadFile(serverConfig.sslConfig.keyPath);
    std::string certificate = Util::ReadFile(serverConfig.sslConfig.certPath);
    sslOpts.pem_key_cert_pairs = {{privateKey, certificate}};

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::SslServerCredentials(sslOpts));
    builder.RegisterService(pAccountService.get());
    // auto p= AccountServiceImpl(serverConfig.aliApiConfig, serverConfig.smsConfig);
    // builder.RegisterService(&p);
    pGrpcServer = builder.BuildAndStart();
    std::cout << "Server listening on " << serverAddress << std::endl;
    pGrpcServer->Wait();
}







