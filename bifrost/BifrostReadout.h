// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Bifrost UDP readout generator class
///
//===----------------------------------------------------------------------===//
#pragma once

#include <GenericReadout.h>

class BifrostReadout : public GenericReadout {
public:
  using GenericReadout::GenericReadout;

  static constexpr uint8_t Detector{52};

  // As per BIFROST ICD
  struct BifrostData {
    uint8_t Ring;
    uint8_t FEN;
    uint16_t Length;
    uint32_t TimeHigh;
    uint32_t TimeLow;
    uint8_t OMFlag;
    uint8_t Tube;
    uint16_t Unused16;
    uint16_t AmplA;
    uint16_t AmplB;
    uint32_t Unused32;
  } __attribute__((packed));

  // Adds a readout to the transmission buffer.
  // If there is no room left, transmit and initialize a new packet
  int addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh, uint32_t TimeLow,
                 uint8_t Tube, uint16_t AmplA, uint16_t AmplB);
};
