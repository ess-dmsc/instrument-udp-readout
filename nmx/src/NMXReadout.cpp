// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief NMX UDP readout generator class implementation
///
//===----------------------------------------------------------------------===//
#include <NMXReadout.h>

int NMXReadout::addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh,
                               uint32_t TimeLow, uint8_t VMM, uint8_t Channel) {
  if (DataSize >= MaxDataSize) {
    send();
    newPacket();
  }
  struct NMXData *dp = (struct NMXData *)(buffer + DataSize);
  dp->Ring = Ring;
  dp->FEN = FEN;
  dp->DataLength = sizeof(struct NMXData);
  dp->TimeHigh = TimeHigh;
  dp->TimeLow = TimeLow;
  dp->VMM = VMM;
  dp->Channel = Channel;


  DataSize += dp->DataLength;
  hp->TotalLength = DataSize;
  return 0;
}
