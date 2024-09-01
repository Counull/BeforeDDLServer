//
// Created by lxxr on 9/1/24.
//

#include "AccountServiceImpl.h"

AccountServiceImpl::~AccountServiceImpl() {

}

grpc::Status AccountServiceImpl::Register(::grpc::ServerContext *context, const ::Authority::RegisterRequest *request,
                                          ::Authority::RegisterResponse *response) {
    std::cout << "Register called" << std::endl;
    return Service::Register(context, request, response);
}

grpc::Status AccountServiceImpl::Login(::grpc::ServerContext *context, const ::Authority::LoginRequest *request,
                                       ::Authority::LoginResponse *response) {
    return Service::Login(context, request, response);
}

grpc::Status
AccountServiceImpl::SendSmsCode(::grpc::ServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                                ::Authority::SendSmsCodeResponse *response) {
    return Service::SendSmsCode(context, request, response);
}

grpc::Status
AccountServiceImpl::VerifySmsCode(::grpc::ServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                                  ::Authority::VerifySmsCodeResponse *response) {
    return Service::VerifySmsCode(context, request, response);
}
