// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief DREAM UDP readout generator class
///
//===----------------------------------------------------------------------===//
#pragma once

#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string>
#include <sys/socket.h>
#include <inttypes.h>

class GenericReadout {
public:
  // Header common to all ESS readout data
  // Reviewed ICD (version 2) packet header version 0
  // ownCloud: https://project.esss.dk/owncloud/index.php/s/DWNer23727TiI1x
  struct PacketHeaderV0 {
    uint8_t Padding0;
    uint8_t Version;
    uint32_t CookieAndType;
    uint16_t TotalLength;
    uint8_t OutputQueue;
    uint8_t TimeSource;
    uint32_t PulseHigh;
    uint32_t PulseLow;
    uint32_t PrevPulseHigh;
    uint32_t PrevPulseLow;
    uint32_t SeqNum;
  } __attribute__((packed));

  GenericReadout(uint8_t DetectorType, std::string IpAddress, int UDPPort)
      : Type(DetectorType), ipaddr(IpAddress), port(UDPPort) {
    sockOpen(ipaddr, port);
  }

  // send the current data buffer
  int send();

  // Update the pulse and previous pulse times
  void setPulseTime(uint32_t PHI, uint32_t PLO, uint32_t PPHI, uint32_t PPLO);

  // Initialize a new packet with no readouts
  void newPacket();

protected:
  // setup socket for transmission
  void sockOpen(std::string ipaddr, int port);

  // Packet header
  uint32_t phi{0}; // pulse and prev pulse high and low
  uint32_t plo{0};
  uint32_t pphi{0};
  uint32_t pplo{0};

  int SeqNum{0};
  int OutputQueue{0};
  int Type{0x34};

  // TX Buffer
  PacketHeaderV0 *hp;
  char buffer[9000];
  const int MaxDataSize{8950};
  int DataSize{0};
  // IP and port number
  std::string ipaddr{""};
  int port{9000};
  // BSD Socket specifics
  int fd; // socket file descriptor
  struct sockaddr_in remoteSockAddr;
};
