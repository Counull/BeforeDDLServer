#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <unordered_map>
#include <grpcpp/grpcpp.h>
#include "ConfigJsonSerialize.h"
#include "Authority.grpc.pb.h"

class Application {
public:
    Application();

    ~Application();

    int run(const ServerConfig &serverConfig);


private:
    void createChannel();

    void createService();


};

#endif