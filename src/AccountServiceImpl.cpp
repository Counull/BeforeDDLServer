//
// Created by lxxr on 9/1/24.
//

#include "AccountServiceImpl.h"
#include "Util.h"

AccountServiceImpl::~AccountServiceImpl() {

}

grpc::Status AccountServiceImpl::Register(::grpc::ServerContext *context, const ::Authority::RegisterRequest *request,
                                          ::Authority::RegisterResponse *response) {
    std::cout << "Register called" << std::endl;
    std::cout << "username: " << request->username() << std::endl;
    std::cout << "phone number: " << request->phone_number() << std::endl;
    std::cout << "password: " << request->password() << std::endl;
    std::cout << "code: " << request->code() << std::endl;
    if (auto kv = registerPhoneCodeMap.find(request->phone_number()); kv == registerPhoneCodeMap.end()) {
        response->set_success(false);
        response->set_message("SMS code not sent");
        return grpc::Status::CANCELLED;
    } else if (kv->second != request->code()) {
        response->set_success(false);
        response->set_message("SMS code not correct");
        return grpc::Status::CANCELLED;
    } else {
        response->set_success(true);
        response->set_message("Succeed!");
        registerPhoneCodeMap.erase(kv->first);
        return grpc::Status::OK;
        //TODO DB operation
    };

    //TODO UNKNOWN ERROR
    return grpc::Status::CANCELLED;
}

grpc::Status AccountServiceImpl::Login(::grpc::ServerContext *context, const ::Authority::LoginRequest *request,
                                       ::Authority::LoginResponse *response) {
    return Service::Login(context, request, response);
}

grpc::Status
AccountServiceImpl::SendSmsCode(::grpc::ServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                                ::Authority::SendSmsCodeResponse *response) {

    //Check sms service available
    if (!aliSmsSupport.has_value()) {
        response->set_success(false);
        response->set_message("Sms service not available");
        return grpc::Status::CANCELLED;
    }
    //Check purpose
    if (request->purpose() == Authority::SmsCodePurpose::UNKNOWN) {
        response->set_success(false);
        response->set_message("Witch purpose do you want to use this code?");
        return grpc::Status::CANCELLED;
    }
    if (!Util::IsValidPhoneNumber(request->phone_number())) {
        response->set_success(false);
        response->set_message("Phone number not valid");
        return grpc::Status::CANCELLED;
    }

    //Generate code
    auto code = Util::GenerateSixDigitRandomNumber();
    if (aliSmsSupport.value().SendSms(request->phone_number(), code)) {
        auto &phoneCodeMap =
                request->purpose() == Authority::SmsCodePurpose::LOGIN ? loginPhoneCodeMap : registerPhoneCodeMap;
        phoneCodeMap.emplace(request->phone_number(), code);
        return grpc::Status::OK;
    } else {
        return grpc::Status::CANCELLED;
    }

}

grpc::Status
AccountServiceImpl::VerifySmsCode(::grpc::ServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                                  ::Authority::VerifySmsCodeResponse *response) {
    return Service::VerifySmsCode(context, request, response);
}

AccountServiceImpl::AccountServiceImpl(const AliApiConfig &apiConfig, const SMSConfig &smsConfig) : aliSmsSupport(
        std::make_optional<AliSmsSupport>(apiConfig, smsConfig)) {
}




