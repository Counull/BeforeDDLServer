#include "Application.h"
#include "CmdLineParser.h"

int main(int argc, char *argv[]) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;;

    auto config = CmdLineParser::parse(argc, argv);
    Application app(config);
    return app.run();
}