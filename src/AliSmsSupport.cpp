//
// Created by lxxr on 9/3/24.
//

#include "AliSmsSupport.h"
#include <format>
#include <memory>
#include <utility>

AliSmsSupport::AliSmsSupport(const AliApiConfig &apiConfig, SMSConfig smsConfig)
        : smsConfig(std::move(smsConfig)) {
    AlibabaCloud::InitializeSdk();
    AlibabaCloud::ClientConfiguration configuration(REGION_ID.data());
    configuration.setConnectTimeout(1500);
    configuration.setReadTimeout(4000);
    AlibabaCloud::Credentials credential(apiConfig.accessKeyId, apiConfig.accessKeySecret);
    pClient = std::make_unique<AlibabaCloud::CommonClient>(credential, configuration);
    if (pClient != nullptr) {
        std::cout << "AliSmsSupport init success" << std::endl;
    }
}


AliSmsSupport::AliSmsSupport(AliSmsSupport &&other) noexcept
        : smsConfig(std::move(other.smsConfig)), pClient(std::move(other.pClient)) {
    other.pClient = nullptr;
}

AliSmsSupport &AliSmsSupport::operator=(AliSmsSupport &&other) noexcept {
    if (this != &other) {
        smsConfig = std::move(other.smsConfig);
        pClient = std::move(other.pClient);
        other.pClient = nullptr;
    }
    return *this;
}

AliSmsSupport::~AliSmsSupport() {
    AlibabaCloud::ShutdownSdk();
}

bool AliSmsSupport::SendSms(const std::string &phone, uint code) {
    auto request = createRequest(phone, code);
    auto response = pClient->commonResponse(request);
    if (response.isSuccess()) {
        printf("request success.\n");
        printf("result: %s\n", response.result().payload().c_str());
    } else {
        printf("error: %s\n", response.error().errorMessage().c_str());
        printf("request id: %s\n", response.error().requestId().c_str());
    }
    return response.isSuccess();
}

AlibabaCloud::CommonRequest AliSmsSupport::createRequest(const std::string &phone, uint code) const {
    AlibabaCloud::CommonRequest request(AlibabaCloud::CommonRequest::RequestPattern::RpcPattern);
    auto templateParam = std::format(R"({{"code":"{}"}})", code);
    request.setHttpMethod(AlibabaCloud::HttpRequest::Method::Post);
    request.setDomain(DOMAIN.data());
    request.setVersion(VERSION.data());
    request.setQueryParameter("Action", ACTION.data());
    request.setQueryParameter("PhoneNumbers", phone);
    request.setQueryParameter("SignName", smsConfig.signName);
    request.setQueryParameter("TemplateCode", smsConfig.templateCode);
    request.setQueryParameter("TemplateParam", templateParam);
    std::cout << "SendSms: " << phone << " " << code << std::endl;
    return request;
}

void AliSmsSupport::sendSmsAsync(const std::string &phone, uint code,
                                 std::function<void(std::string, uint)> &&callback) {
    std::cout << "Current function: " << __func__ << std::endl;

    pClient->commonResponseAsync(
            createRequest(phone, code),
            [phone, code, callback](const AlibabaCloud::CommonClient *client,
                                    const AlibabaCloud::CommonRequest &request,
                                    const AlibabaCloud::CommonClient::CommonResponseOutcome &outcome,
                                    const std::shared_ptr<const AlibabaCloud::AsyncCallerContext> &context) {
                std::cout << "SendSmsAsyncCallBack: " << phone << " " << code << std::endl;
                if (outcome.isSuccess()) {
                    callback(phone, code);
                    std::cout << "Request succeeded: " << outcome.result().payload() << std::endl;
                } else {
                    std::cerr << "Request failed: " << outcome.error().errorMessage() << std::endl;
                }
            });
}




