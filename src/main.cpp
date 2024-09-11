#include "Application.h"
#include "CmdLineParser.h"
#include <memory>
#include "absl/flags/parse.h"
#include <grpcpp/grpcpp.h>


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

int main(int argc, char *argv[]) {


    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;;

    Application app(CmdLineParser::parse(argc, argv));


    return app.run();
}