/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * NetworkUtils.h
 * Abstract various network functions.
 * Copyright (C) 2005 Simon Newton
 */

#ifndef INCLUDE_OLA_NETWORK_NETWORKUTILS_H_
#define INCLUDE_OLA_NETWORK_NETWORKUTILS_H_

#include <ola/network/Interface.h>
#include <ola/network/IPV4Address.h>
#include <string>
#include <vector>


namespace ola {
namespace network {

/**
 * @return true if we're big endian, false otherwise.
 */
bool IsBigEndian();

// we define uint8_t versions of these so we can call them with any type.
uint8_t NetworkToHost(uint8_t value);

/**
 * Convert a uint16_t from network to host byte order
 */
uint16_t NetworkToHost(uint16_t value);

/**
 * Convert a uint32_t from network to host byte order
 */
uint32_t NetworkToHost(uint32_t value);
int8_t NetworkToHost(int8_t value);

/**
 * Convert a uint16_t from network to host byte order
 */
int16_t NetworkToHost(int16_t value);

/*
 * Convert a int32_t from network to host byte order
 */
int32_t NetworkToHost(int32_t value);
uint8_t HostToNetwork(uint8_t value);

/**
 * Convert a uint16_t from host to network byte order
 */
uint16_t HostToNetwork(uint16_t value);

/**
 * Convert a uint32_t from host to network byte order
 */
uint32_t HostToNetwork(uint32_t value);
int8_t HostToNetwork(int8_t value);
int16_t HostToNetwork(int16_t value);
int32_t HostToNetwork(int32_t value);

uint8_t HostToLittleEndian(uint8_t value);
uint16_t HostToLittleEndian(uint16_t value);
uint32_t HostToLittleEndian(uint32_t value);
int8_t HostToLittleEndian(int8_t value);
int16_t HostToLittleEndian(int16_t value);
int32_t HostToLittleEndian(int32_t value);
uint8_t LittleEndianToHost(uint8_t value);
uint16_t LittleEndianToHost(uint16_t value);
uint32_t LittleEndianToHost(uint32_t value);
int8_t LittleEndianToHost(int8_t value);
int16_t LittleEndianToHost(int16_t value);
int32_t LittleEndianToHost(int32_t value);

/**
 * Convert a FQDN to a hostname
 * @param fqdn a fully qualified domain name
 * @return the hostname part of the FQDN
 */
std::string HostnameFromFQDN(const std::string &fqdn);

/**
 * Convert a FQDN to a domain
 * @param fqdn a fully qualified domain name
 * @return the domain part of the FQDN
 */
std::string DomainNameFromFQDN(const std::string &fqdn);

/**
 * Return the machine's domain name as a string.
 */
std::string DomainName();


/**
 * Return the machine's fully qualified domain name (FQDN)
 */
std::string FQDN();


/**
 * Return the machine's full hostname (FQDN)
 * @deprecated use FQDN() instead (17 Nov 2013)
 */
std::string FullHostname();

/**
 * Return the machine's hostname
 */
std::string Hostname();

/**
 * Get a vector of name server IP addresses.
 * @param[out] name_servers a pointer to a vector of name servers to populate
 * @return true on success, false otherwise
 */
bool NameServers(std::vector<ola::network::IPV4Address> *name_servers);

/**
 * Get the default route.
 * @param[out] if_index a pointer to an int32 which is updated
 *   with the interface to use for the default route.
 * @param[out] default_gateway a pointer to an IPV4Address which is updated
 *   with the default gateway.
 * @return true if a default route was found, false if there was an error
 *   fetching the routing table.
 * @note if the routing table was read correctly but there was no default
 *   route, if_index will be ola::network::Interface::DEFAULT_INDEX and
 *   default_gateway will be the wildcard address. The latter can be tested for
 *   with default_gateway.IsWildcard().
 */
bool DefaultRoute(int32_t *if_index,
                  ola::network::IPV4Address *default_gateway);
}  // namespace network
}  // namespace ola
#endif  // INCLUDE_OLA_NETWORK_NETWORKUTILS_H_

