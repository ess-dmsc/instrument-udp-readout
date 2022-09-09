// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Bifrost UDP readout generator usage example
///
//===----------------------------------------------------------------------===//
#include <BifrostReadout.h>

int main(int argc, char *argv[]) {

  BifrostReadout bifrost(BifrostReadout::Detector, "127.0.0.1", 9000);

  bifrost.setPulseTime(1, 0, 0, 0);
  bifrost.newPacket();
  for (int i = 0; i < 1000; i++) {
    bifrost.addReadout(0, 0, 1, i, 7, 200, 400);
  }
  bifrost.send();

  return 0;
}
