// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Base class for UDP readout generator class implementation
///
//===----------------------------------------------------------------------===//
#include <GenericReadout.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

/// \brief Use MSG_SIGNAL on Linuxes
#ifdef MSG_NOSIGNAL
#define SEND_FLAGS MSG_NOSIGNAL
#else
#define SEND_FLAGS 0
#endif

void GenericReadout::setPulseTime(uint32_t PHI, uint32_t PLO, uint32_t PPHI,
                                  uint32_t PPLO) {
  phi = PHI;
  plo = PLO;
  pphi = PPHI;
  pplo = PPLO;
}

void GenericReadout::newPacket() {
  memset(buffer, 0x00, sizeof(buffer));
  hp->Padding0 = 0;
  hp->Version = 0;
  hp->CookieAndType = (Type << 24) + 0x535345;
  hp->OutputQueue = OutputQueue;
  hp->TotalLength = sizeof(struct PacketHeaderV0);
  hp->SeqNum = SeqNum++;
  hp->TimeSource = 0;
  hp->PulseHigh = phi;
  hp->PulseLow = plo;
  hp->PrevPulseHigh = pphi;
  hp->PrevPulseLow = pplo;
  DataSize = sizeof(struct PacketHeaderV0);
  return;
}

void GenericReadout::sockOpen(std::string ipaddr, int port) {
  fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd < 0) {
    throw std::runtime_error("socket() failed");
  }

  // zero out the structures
  std::memset((char *)&remoteSockAddr, 0, sizeof(remoteSockAddr));
  remoteSockAddr.sin_family = AF_INET;
  remoteSockAddr.sin_port = htons(port);

  int ret = inet_aton(ipaddr.c_str(), &remoteSockAddr.sin_addr);
  if (ret == 0) {
    printf("setRemoteSocket(): invalid ip address %s", ipaddr.c_str());
    throw std::runtime_error("sock_open() failed");
  }

  hp = (PacketHeaderV0 *)&buffer[0];
}


int GenericReadout::send() {
  //printf("Send packet with length %u\n", DataSize);
  int ret = sendto(fd, (char *)buffer, DataSize, SEND_FLAGS,
                   (struct sockaddr *)&remoteSockAddr, sizeof(remoteSockAddr));
  if (ret < 0) {
    printf("socket sendto() failed: returns %d\n", ret);
  }
  return ret;
}
