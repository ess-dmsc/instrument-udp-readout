// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Bifrost UDP readout generator class implementation
///
//===----------------------------------------------------------------------===//
#include <BifrostReadout.h>

int BifrostReadout::addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh,
                               uint32_t TimeLow, uint8_t Tube, uint16_t AmplA,
                               uint16_t AmplB) {
  if (DataSize >= MaxDataSize) {
    send();
    newPacket();
  }
  struct BifrostData *dp = (struct BifrostData *)(buffer + DataSize);
  dp->Ring = Ring;
  dp->FEN = FEN;
  dp->Length = sizeof(struct BifrostData);
  dp->TimeHigh = TimeHigh;
  dp->TimeLow = TimeLow;
  dp->Tube = Tube;
  dp->AmplA = AmplA;
  dp->AmplB = AmplB;

  DataSize += dp->Length;
  hp->TotalLength = DataSize;
  return 0;
}
