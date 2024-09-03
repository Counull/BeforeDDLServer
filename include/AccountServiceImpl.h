//
// Created by lxxr on 9/1/24.
//

#ifndef BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H
#define BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H

#include <optional>
#include "Authority.grpc.pb.h"
#include "AliSmsSupport.h"

class AccountServiceImpl final : public Authority::AccountService::Service {
public:

    explicit AccountServiceImpl(const AliApiConfig &apiConfig, const SMSConfig &smsConfig);

    ~AccountServiceImpl() override;

    grpc::Status Register(::grpc::ServerContext *context, const ::Authority::RegisterRequest *request,
                          ::Authority::RegisterResponse *response) override;

    grpc::Status Login(::grpc::ServerContext *context, const ::Authority::LoginRequest *request,
                       ::Authority::LoginResponse *response) override;

    grpc::Status SendSmsCode(::grpc::ServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                             ::Authority::SendSmsCodeResponse *response) override;

    grpc::Status VerifySmsCode(::grpc::ServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                               ::Authority::VerifySmsCodeResponse *response) override;

private:
    std::optional<AliSmsSupport> aliSmsSupport;
    std::unordered_map<std::string, uint> registerPhoneCodeMap;
    std::unordered_map<std::string, uint> loginPhoneCodeMap;
};


#endif //BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H
