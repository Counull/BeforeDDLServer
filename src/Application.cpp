#include "Application.h"

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
    AccountServiceImpl accountService;
    grpc::ServerBuilder builder;
    grpc::SslServerCredentialsOptions sslOpts;
    std::string privateKey = Util::readFile(serverConfig.sslConfig.keyPath);
    std::string certificate = Util::readFile(serverConfig.sslConfig.certPath);
    sslOpts.pem_key_cert_pairs = {{privateKey, certificate}};
    builder.AddListeningPort(serverAddress, grpc::SslServerCredentials(sslOpts));
    builder.RegisterService(&accountService);
    builder.SetMaxReceiveMessageSize(std::numeric_limits<int>::max());
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << serverAddress << std::endl;

    server->Wait();
    //pHelloService->Wait();
}

void Application::createChannel() {
    pChannel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials());
}
