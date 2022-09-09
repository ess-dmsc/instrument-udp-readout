// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief DREAM UDP readout generator class
///
//===----------------------------------------------------------------------===//
#pragma once

#include <GenericReadout.h>
#include <string>

class DreamReadout : public GenericReadout {
public:
  using GenericReadout::GenericReadout;

  static constexpr uint8_t Detector{96};

  // As per DREAM ICD
  struct DreamData {
    uint8_t Ring;
    uint8_t FEN;
    uint16_t Length;
    uint32_t TimeHigh;
    uint32_t TimeLow;
    uint8_t OperatingMode;
    uint8_t Unused;
    uint8_t Cathode;
    uint8_t Anode;
  } __attribute__((packed));

  // Adds a readout to the transmission buffer.
  // If there is no room left, transmit and initialize a new packet
  int addReadout(uint8_t Ring, uint8_t FEN, uint32_t TimeHigh, uint32_t TimeLow,
                 uint8_t Cathode, uint8_t Anode);
};
