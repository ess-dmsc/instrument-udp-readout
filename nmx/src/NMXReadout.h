// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief NMX UDP readout generator class
///
//===----------------------------------------------------------------------===//
#pragma once

#include <GenericReadout.h>

class NMXReadout : public GenericReadout {
public:
  using GenericReadout::GenericReadout;

  static constexpr uint8_t Detector{56};

  // As per NMX ICD
  struct NMXData {
    uint8_t Ring;
    uint8_t FEN;
    uint16_t DataLength;
    uint32_t TimeHigh;
    uint32_t TimeLow;
    uint16_t BC;
    uint16_t OTADC;
    uint8_t GEO;
    uint8_t TDC;
    uint8_t VMM;
    uint8_t Channel;
  } __attribute__((packed));

  // Adds a readout to the transmission buffer.
  // If there is no room left, transmit and initialize a new packet
  int addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh, uint32_t TimeLow,
                 uint8_t VMM, uint8_t Channel);
};
