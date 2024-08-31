#include "Application.h"

Application::Application() = default;

Application::~Application() = default;

int Application::run(const ServerConfig &serverConfig) {

    createService();
    return 0;
}

void Application::createService() {

    Authority::AccountService accountService;

}

void Application::createChannel() {

    auto channel = grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());


}
