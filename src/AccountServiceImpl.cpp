//
// Created by lxxr on 9/1/24.
//

#include "AccountServiceImpl.h"
#include "Util.h"


AccountServiceImpl::AccountServiceImpl(const AliApiConfig &apiConfig, const SMSConfig &smsConfig,
                                       const std::shared_ptr<RedisConnection> &redis) : aliSmsSupport(
        std::make_optional<AliSmsSupport>(apiConfig, smsConfig)), pRedisConnection(redis) {
    std::cout << pRedisConnection.get() << "  " << redis.get() << std::endl;
}

AccountServiceImpl::~AccountServiceImpl() { std::cout << "Current function: " << __func__ << std::endl; };

grpc::Status AccountServiceImpl::Register(::grpc::ServerContext *context, const ::Authority::RegisterRequest *request,
                                          ::Authority::RegisterResponse *response) {

    std::cout << request->DebugString() << std::endl;
    if (auto kv = phoneCodeMap.find(request->phone_number()); kv == phoneCodeMap.end()) {
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
        phoneCodeMap.erase(kv->first);
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

    std::cout << "Current function: " << __func__ << std::endl;
    if (!CheckSendSmsRequest(request, response)) {
        return grpc::Status::CANCELLED;
    }

    //Generate code
    auto code = Util::GenerateSixDigitRandomNumber();
    if (aliSmsSupport.value().SendSms(request->phone_number(), code)) {
        phoneCodeMap.emplace(request->phone_number(), code);
        return grpc::Status::OK;
    } else {
        return grpc::Status::CANCELLED;
    }

}

grpc::ServerUnaryReactor *
AccountServiceImpl::SendSmsCode(::grpc::CallbackServerContext *context, const ::Authority::SendSmsCodeRequest *request,
                                ::Authority::SendSmsCodeResponse *response) {

    grpc::ServerUnaryReactor *reactor = context->DefaultReactor();
    if (!CheckSendSmsRequest(request, response)) {
        reactor->Finish(grpc::Status::CANCELLED);
    }

    //Generate code
    auto code = Util::GenerateSixDigitRandomNumber();
    std::weak_ptr<AccountServiceImpl> weakThis = shared_from_this();

    auto callback = [reactor, weakThis, response](auto phoneNum, auto code) {
        auto pThis = weakThis.lock();
        if (pThis != nullptr) {
            pThis->pRedisConnection->getKeyAsyncThreadSafe("123123",
                                                           [](auto rep) {
                                                               std::cout << "Redis reply:GET " << rep << std::endl;
                                                           });
            pThis->pRedisConnection->setKeyAsyncThreadSafe(phoneNum, std::to_string(code),
                                                           [reactor, weakThis, response](auto reply) {
                                                               std::cout << "Redis reply:SET " << std::endl;
                                                               if (RedisConnection::ReplyIsOK(reply)) {
                                                                   response->set_success(true);
                                                                   reactor->Finish(grpc::Status::OK);
                                                                   return;
                                                               }
                                                               response->set_success(false);
                                                               reactor->Finish(grpc::Status::CANCELLED);
                                                           });

            return;
        }
        reactor->Finish(grpc::Status::CANCELLED);
    };

    aliSmsSupport.value().sendSmsAsync(request->phone_number(), code, std::move(callback));

    return reactor;
}


grpc::Status
AccountServiceImpl::VerifySmsCode(::grpc::ServerContext *context, const ::Authority::VerifySmsCodeRequest *request,
                                  ::Authority::VerifySmsCodeResponse *response) {
    return Service::VerifySmsCode(context, request, response);
}

grpc::ServerUnaryReactor *
AccountServiceImpl::Register(::grpc::CallbackServerContext *context, const ::Authority::RegisterRequest *request,
                             ::Authority::RegisterResponse *response) {
    return WithCallbackMethod_Register::Register(context, request, response);
}

grpc::ServerUnaryReactor *
AccountServiceImpl::Login(::grpc::CallbackServerContext *context, const ::Authority::LoginRequest *request,
                          ::Authority::LoginResponse *response) {
    return WithCallbackMethod_Login::Login(context, request, response);
}


grpc::ServerUnaryReactor *AccountServiceImpl::VerifySmsCode(::grpc::CallbackServerContext *context,
                                                            const ::Authority::VerifySmsCodeRequest *request,
                                                            ::Authority::VerifySmsCodeResponse *response) {
    return WithCallbackMethod_VerifySmsCode::VerifySmsCode(context, request, response);
}


bool AccountServiceImpl::CheckSendSmsRequest(const ::Authority::SendSmsCodeRequest *request,
                                             ::Authority::SendSmsCodeResponse *response) {
    std::cout << request->DebugString() << std::endl;
    //Check sms service available
    if (!aliSmsSupport.has_value()) {
        response->set_success(false);
        response->set_message("Sms service not available");
        return false;
    }
    //Check purpose
    if (request->purpose() == Authority::SmsCodePurpose::UNKNOWN) {
        response->set_success(false);
        response->set_message("Witch purpose do you want to use this code?");
        return false;
    }
    if (!Util::IsValidPhoneNumber(request->phone_number())) {
        response->set_success(false);
        response->set_message("Phone number not valid");
        return false;
    }
    return true;
}







