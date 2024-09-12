//
// Created by lxxr on 9/12/24.
//

#ifndef BEFOREDDLSERVER_CONFIGBOOSTJSONSERIALIZE_H
#define BEFOREDDLSERVER_CONFIGBOOSTJSONSERIALIZE_H

#include <boost/hana.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Config.h"

BOOST_HANA_ADAPT_STRUCT(NetworkConfig, ip, port);
BOOST_HANA_ADAPT_STRUCT(TencentApiConfig, secretId, secretKey);
BOOST_HANA_ADAPT_STRUCT(AliApiConfig, accessKeyId, accessKeySecret);
BOOST_HANA_ADAPT_STRUCT(SMSConfig, signName, templateCode);
BOOST_HANA_ADAPT_STRUCT(SSLConfig, certPath, keyPath);
BOOST_HANA_ADAPT_STRUCT(RedisConfig, ip, port, password, dbIndex);
BOOST_HANA_ADAPT_STRUCT(ServerConfig, networkConfig, tencentApiConfig, aliApiConfig, smsConfig, sslConfig, redisConfig);


namespace hana = boost::hana;
namespace BoostJsonSerialize {

    template<typename T>
    void from_json(const boost::property_tree::ptree &pt, T &obj) {
        hana::for_each(hana::accessors<T>(), [&](auto accessor) {
            auto name = hana::to<const char *>(hana::first(accessor));
            auto &member = hana::second(accessor)(obj);
            using MemberType = std::decay_t<decltype(member)>;
            if constexpr (hana::Struct<MemberType>::value) {
                from_json(pt.get_child(name), member);
            } else {
                member = pt.get<MemberType>(name);
            }
        });
    }

    template<typename T>
    void to_json(boost::property_tree::ptree &pt, const T &obj) {
        hana::for_each(hana::accessors<T>(), [&](auto accessor) {
            auto name = hana::to<const char *>(hana::first(accessor));
            const auto &member = hana::second(accessor)(obj);
            if constexpr (hana::Struct<std::decay_t<decltype(member)>>::value) {
                boost::property_tree::ptree child;
                to_json(child, member);
                pt.add_child(name, child);
            } else {
                pt.put(name, member);
            }
        });
    }

    template<>
    void to_json<boost::property_tree::ptree>(boost::property_tree::ptree &pt, const boost::property_tree::ptree &obj) {
        pt = obj;
    }
}

#endif //BEFOREDDLSERVER_CONFIGBOOSTJSONSERIALIZE_H