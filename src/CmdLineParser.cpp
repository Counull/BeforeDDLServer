//
// Created by lxxr on 8/30/24.
//
#include <fstream>
#include "CmdLineParser.h"
#include "ConfigBoostJsonSerialize.h"

ServerConfig CmdLineParser::parse(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            exit(0);
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                i++;
                return CmdLineParser::parseConfigFileWithBoost(argv[i]);
            } else {
                printf("Error: -c option requires a file name\n");
                exit(1);
            }
        } else {
            printf("Error: Unknown option: %s\n", argv[i]);
            exit(1);
        }
    }

    ServerConfig serverConfig;
    return serverConfig;
}

void CmdLineParser::printHelp() {

}

ServerConfig CmdLineParser::parseConfigFile(const std::string_view &configFilePath) {
    std::ifstream file(configFilePath.data());
    auto json = nlohmann::json::parse(file);
    return json.template get<ServerConfig>();
}

ServerConfig CmdLineParser::parseConfigFileWithBoost(const std::string_view &configFilePath) {
    std::ifstream file(configFilePath.data());
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(file, pt);
    ServerConfig config;
    BoostJsonSerialize::from_json(pt, config);
    return config;
}