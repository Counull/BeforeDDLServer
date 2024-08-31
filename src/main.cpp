#include "Application.h"
#include "CmdLineParser.h"

int main(int argc, char *argv[]) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current working directory: " << currentPath << std::endl;;

    Application app;
    auto config = CmdLineParser::parse(argc, argv);
    return app.run(config);


}