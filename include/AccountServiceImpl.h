//
// Created by lxxr on 9/1/24.
//

#ifndef BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H
#define BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H

#include <optional>
#include "Authority.grpc.pb.h"
#include "AliSmsSupport.h"

class AccountServiceImpl final
        : public Authority::AccountService::CallbackService, public std::enable_shared_from_this<AccountServiceImpl> {
public:

    explicit AccountServiceImpl(const AliApiConfig &apiConfig, const SMSConfig &smsConfig);

    ~AccountServiceImpl()
    override;

    grpc::Status Register(::grpc::ServerContext *context, const ::Authority::RegisterRequest *request,
                          ::Authority::RegisterResponse *response) override;

    grpc::Status Login(::grpc::ServerContext *context, const ::Authority::LoginRequest *request,
                       ::Authority::LoginResponse *response) override;

    grpc::Status SendSmsCode(::grpc::ServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                             ::Authority::SendSmsCodeResponse *response) override;

    grpc::Status VerifySmsCode(::grpc::ServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                               ::Authority::VerifySmsCodeResponse *response) override;

    grpc::ServerUnaryReactor *
    Register(::grpc::CallbackServerContext *context, const ::Authority::RegisterRequest *request,
             ::Authority::RegisterResponse *response) override;

    grpc::ServerUnaryReactor *
    Login(::grpc::CallbackServerContext *context, const ::Authority::LoginRequest *request,
          ::Authority::LoginResponse *response) override;

    grpc::ServerUnaryReactor *
    SendSmsCode(::grpc::CallbackServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                ::Authority::SendSmsCodeResponse *response) override;

    grpc::ServerUnaryReactor *
    VerifySmsCode(::grpc::CallbackServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                  ::Authority::VerifySmsCodeResponse *response) override;

private:
    std::optional<AliSmsSupport> aliSmsSupport;
    std::unordered_map<std::string, uint> phoneCodeMap;


private:
    bool CheckSendSmsRequest(const ::Authority::SendSmsCodeRequest *request,
                             ::Authority::SendSmsCodeResponse *response);

};


#endif //BEFOREDDLSERVER_ACCOUNTSERVICEIMPL_H
