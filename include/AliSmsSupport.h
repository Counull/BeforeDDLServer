//
// Created by lxxr on 9/3/24.
//

#ifndef BEFOREDDLSERVER_ALISMSSUPPORT_H
#define BEFOREDDLSERVER_ALISMSSUPPORT_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/core/CommonRequest.h>
#include <alibabacloud/core/CommonClient.h>
#include <alibabacloud/core/CommonResponse.h>
#include <memory>
#include "Config.h"

class AliSmsSupport {

public:
    AliSmsSupport() = delete;

    AliSmsSupport(const AliSmsSupport &) = delete;

    AliSmsSupport &operator=(const AliSmsSupport &) = delete;

    AliSmsSupport(AliApiConfig apiConfig, SMSConfig smsConfig);

    AliSmsSupport(AliSmsSupport &&other) noexcept;

    AliSmsSupport &operator=(AliSmsSupport &&other) noexcept;

    ~AliSmsSupport();


    void sendSmsAsync(const std::string &phone, uint code);

    bool SendSms(const std::string &phone, uint code);

private:
    static constexpr std::string_view REGION_ID = "cn-beijing";
    static constexpr std::string_view DOMAIN = "dysmsapi.aliyuncs.com";
    static constexpr std::string_view VERSION = "2017-05-25";
    static constexpr std::string_view ACTION = "SendSms";

    std::unique_ptr<AlibabaCloud::CommonClient> pClient;
    AliApiConfig aliApiConfig;
    SMSConfig smsConfig;

    AlibabaCloud::CommonRequest createRequest(const std::string &phone, uint code) const;

};


#endif //BEFOREDDLSERVER_ALISMSSUPPORT_H
