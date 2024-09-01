#include "Application.h"
#include "AccountServiceImpl.h"
#include "absl/log/initialize.h"

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
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&accountService);
    pAccountService = builder.BuildAndStart();
    std::cout << "Server listening on " << serverAddress << std::endl;
    pAccountService->Wait();

}

void Application::createChannel() {
    pChannel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials());
}
