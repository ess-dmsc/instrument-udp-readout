// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Bifrost UDP readout generator class implementation
///
//===----------------------------------------------------------------------===//
#include <DreamReadout.h>

int DreamReadout::addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh,
                               uint32_t TimeLow, uint8_t Cathode,
                               uint8_t Anode) {
  if (DataSize >= MaxDataSize) {
    send();
    newPacket();
  }
  struct DreamData *dp = (struct DreamData *)(buffer + DataSize);
  dp->Ring = Ring;
  dp->FEN = FEN;
  dp->Length = sizeof(struct DreamData);
  dp->TimeHigh = TimeHigh;
  dp->TimeLow = TimeLow;
  dp->Cathode = Cathode;
  dp->Anode = Anode;

  DataSize += dp->Length;
  hp->TotalLength = DataSize;
  return 0;
}
