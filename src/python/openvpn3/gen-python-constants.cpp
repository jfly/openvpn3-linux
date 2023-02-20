//  OpenVPN 3 Linux client -- Next generation OpenVPN client
//
//  SPDX-License-Identifier: AGPL-3.0-only
//
//  Copyright (C) 2017 - 2023  OpenVPN Inc <sales@openvpn.net>
//  Copyright (C) 2017 - 2023  David Sommerseth <davids@openvpn.net>
//  Copyright (C) 2018 - 2023  Lev Stipakov <lev@openvpn.net>
//  Copyright (C) 2021 - 2023  Heiko Hund <heiko@openvpn.net>
//

/**
 * @file   gen-python-constants.cpp
 *
 * @brief  Generates Python Enum classes of constants defined in
 *         dbus/constants.hpp
 */

#include <cstdint>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "config.h"
#include "dbus/constants.hpp"
#include "netcfg/netcfg-changetype.hpp"
#include "sessionmgr/sessionmgr-events.hpp"


enum class FlagType
{
    NONE = 0,
    INTFLAG = 1
};

template <class T>
struct ConstantMapping
{
    ConstantMapping(const std::string name, T value)
        : name(name), value(value)
    {
    }

    const std::string name;
    T value;
};

#define MAP(t, m, n, v) m.push_back(ConstantMapping<t>(n, t::v))

template <class T>
void Generator(std::string name, std::vector<ConstantMapping<T>> mapping, FlagType flagtype = FlagType::NONE)
{
    std::stringstream c;

    switch (flagtype)
    {
    case FlagType::INTFLAG:
        c << "class " << name << "(IntFlag):" << std::endl;
        break;
    case FlagType::NONE:
    default:
        c << "class " << name << "(Enum):" << std::endl;
    }
    for (auto &m : mapping)
    {
        c << "    " << m.name << " = " << (unsigned int)m.value << std::endl;
    }

    std::cout << c.str() << std::endl;
    std::cout << std::endl;
}


int main(int argc, char **argv)
{

    std::cout << "#" << std::endl
              << "# Generated by " << argv[0] << std::endl
              << "# as part of the project build." << std::endl
              << "#" << std::endl
              << "# This file is part of openvpn3-linux, licensed" << std::endl
              << "# under AGPLv3.  Please see the main COPYRIGHT.md" << std::endl
              << "# file packaged with the project for more details." << std::endl
              << "#" << std::endl
              << "# Do not modify this file.  This file needs to be" << std::endl
              << "# regenerated each time any of the OpenVPN 3 Linux" << std::endl
              << "# constants are modified." << std::endl
              << "#" << std::endl
              << std::endl;

    // This requires Python 3.6 or newer
    // Older Python releases are no longer supported
    std::cout << "from enum import Enum, IntFlag" << std::endl
              << std::endl;

    std::cout << "VERSION = '" << PACKAGE_GUIVERSION << "'"
              << std::endl
              << std::endl;

    std::vector<ConstantMapping<StatusMajor>> maj;
    MAP(StatusMajor, maj, "UNSET", UNSET);
    MAP(StatusMajor, maj, "CFG_ERROR", CONFIG);
    MAP(StatusMajor, maj, "CONNECTION", CONNECTION);
    MAP(StatusMajor, maj, "SESSION", SESSION);
    MAP(StatusMajor, maj, "PKCS11", PKCS11);
    MAP(StatusMajor, maj, "PROCESS", PROCESS);
    Generator("StatusMajor", maj);

    std::vector<ConstantMapping<StatusMinor>> min;
    MAP(StatusMinor, min, "UNSET", UNSET);
    MAP(StatusMinor, min, "CFG_ERROR", CFG_ERROR);
    MAP(StatusMinor, min, "CFG_OK", CFG_OK);
    MAP(StatusMinor, min, "CFG_INLINE_MISSING", CFG_INLINE_MISSING);
    MAP(StatusMinor, min, "CFG_REQUIRE_USER", CFG_REQUIRE_USER);
    MAP(StatusMinor, min, "CONN_INIT", CONN_INIT);
    MAP(StatusMinor, min, "CONN_CONNECTING", CONN_CONNECTING);
    MAP(StatusMinor, min, "CONN_CONNECTED", CONN_CONNECTED);
    MAP(StatusMinor, min, "CONN_DISCONNECTING", CONN_DISCONNECTING);
    MAP(StatusMinor, min, "CONN_DISCONNECTED", CONN_DISCONNECTED);
    MAP(StatusMinor, min, "CONN_FAILED", CONN_FAILED);
    MAP(StatusMinor, min, "CONN_AUTH_FAILED", CONN_AUTH_FAILED);
    MAP(StatusMinor, min, "CONN_RECONNECTING", CONN_RECONNECTING);
    MAP(StatusMinor, min, "CONN_PAUSING", CONN_PAUSING);
    MAP(StatusMinor, min, "CONN_PAUSED", CONN_PAUSED);
    MAP(StatusMinor, min, "CONN_RESUMING", CONN_RESUMING);
    MAP(StatusMinor, min, "CONN_DONE", CONN_DONE);
    MAP(StatusMinor, min, "SESS_NEW", SESS_NEW);
    MAP(StatusMinor, min, "SESS_BACKEND_COMPLETED", SESS_BACKEND_COMPLETED);
    MAP(StatusMinor, min, "SESS_REMOVED", SESS_REMOVED);
    MAP(StatusMinor, min, "SESS_AUTH_USERPASS", SESS_AUTH_USERPASS);
    MAP(StatusMinor, min, "SESS_AUTH_CHALLENGE", SESS_AUTH_CHALLENGE);
    MAP(StatusMinor, min, "SESS_AUTH_URL", SESS_AUTH_URL);
    MAP(StatusMinor, min, "PKCS11_SIGN", PKCS11_SIGN);
    MAP(StatusMinor, min, "PKCS11_ENCRYPT", PKCS11_ENCRYPT);
    MAP(StatusMinor, min, "PKCS11_DECRYPT", PKCS11_DECRYPT);
    MAP(StatusMinor, min, "PKCS11_VERIFY", PKCS11_VERIFY);
    MAP(StatusMinor, min, "PROC_STARTED", PROC_STARTED);
    MAP(StatusMinor, min, "PROC_STOPPED", PROC_STOPPED);
    MAP(StatusMinor, min, "PROC_KILLED", PROC_KILLED);
    Generator("StatusMinor", min);

    std::vector<ConstantMapping<SessionManager::EventType>> smgrev;
    MAP(SessionManager::EventType, smgrev, "SESS_CREATED", SESS_CREATED);
    MAP(SessionManager::EventType, smgrev, "SESS_DESTROYED", SESS_DESTROYED);
    Generator("SessionManagerEventType", smgrev);

    std::vector<ConstantMapping<ClientAttentionType>> client_att_type;
    MAP(ClientAttentionType, client_att_type, "UNSET", UNSET);
    MAP(ClientAttentionType, client_att_type, "CREDENTIALS", CREDENTIALS);
    MAP(ClientAttentionType, client_att_type, "PKCS11", PKCS11);
    MAP(ClientAttentionType, client_att_type, "ACCESS_PERM", ACCESS_PERM);
    Generator("ClientAttentionType", client_att_type);

    std::vector<ConstantMapping<ClientAttentionGroup>> client_att_group;
    MAP(ClientAttentionGroup, client_att_group, "UNSET", UNSET);
    MAP(ClientAttentionGroup, client_att_group, "USER_PASSWORD", USER_PASSWORD);
    MAP(ClientAttentionGroup, client_att_group, "HTTP_PROXY_CREDS", HTTP_PROXY_CREDS);
    MAP(ClientAttentionGroup, client_att_group, "PK_PASSPHRASE", PK_PASSPHRASE);
    MAP(ClientAttentionGroup, client_att_group, "CHALLENGE_STATIC", CHALLENGE_STATIC);
    MAP(ClientAttentionGroup, client_att_group, "CHALLENGE_DYNAMIC", CHALLENGE_DYNAMIC);
    MAP(ClientAttentionGroup, client_att_group, "CHALLENGE_AUTH_PENDING", CHALLENGE_AUTH_PENDING);
    MAP(ClientAttentionGroup, client_att_group, "PKCS11_SIGN", PKCS11_SIGN);
    MAP(ClientAttentionGroup, client_att_group, "PKCS11_DECRYPT", PKCS11_DECRYPT);
    MAP(ClientAttentionGroup, client_att_group, "OPEN_URL", OPEN_URL);
    Generator("ClientAttentionGroup", client_att_group);

    std::vector<ConstantMapping<NetCfgChangeType>> netcfg_changetype;
    MAP(NetCfgChangeType, netcfg_changetype, "UNSET", UNSET);
    MAP(NetCfgChangeType, netcfg_changetype, "DEVICE_ADDED", DEVICE_ADDED);
    MAP(NetCfgChangeType, netcfg_changetype, "DEVICE_REMOVED", DEVICE_REMOVED);
    MAP(NetCfgChangeType, netcfg_changetype, "IPADDR_ADDED", IPADDR_ADDED);
    MAP(NetCfgChangeType, netcfg_changetype, "IPADDR_REMOVED", IPADDR_REMOVED);
    MAP(NetCfgChangeType, netcfg_changetype, "ROUTE_ADDED", ROUTE_ADDED);
    MAP(NetCfgChangeType, netcfg_changetype, "ROUTE_REMOVED", ROUTE_REMOVED);
    MAP(NetCfgChangeType, netcfg_changetype, "ROUTE_EXCLUDED", ROUTE_EXCLUDED);
    MAP(NetCfgChangeType, netcfg_changetype, "DNS_SERVER_ADDED", DNS_SERVER_ADDED);
    MAP(NetCfgChangeType, netcfg_changetype, "DNS_SERVER_REMOVED", DNS_SERVER_REMOVED);
    MAP(NetCfgChangeType, netcfg_changetype, "DNS_SEARCH_ADDED", DNS_SEARCH_ADDED);
    MAP(NetCfgChangeType, netcfg_changetype, "DNS_SEARCH_REMOVED", DNS_SEARCH_REMOVED);
    Generator("NetCfgChangeType", netcfg_changetype, FlagType::INTFLAG);

    return 0;
}
