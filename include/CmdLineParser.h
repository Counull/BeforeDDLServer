//
// Created by lxxr on 8/30/24.
//

#ifndef BEFOREDDLSERVER_CMDLINEPARASER_H
#define BEFOREDDLSERVER_CMDLINEPARASER_H

#include <iostream>
#include "ConfigJsonSerialize.h"

class CmdLineParser {

public:
    static ServerConfig parse(int argc, char *argv[]);

private:
    static void printHelp();
    static ServerConfig parseConfigFile(const std::string_view &configFilePath);
};


#endif //BEFOREDDLSERVER_CMDLINEPARASER_H
