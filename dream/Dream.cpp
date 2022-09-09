// Copyright (C) 2022 European Spallation Source, ERIC. See LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief DREAM UDP readout generator usage example
///
//===----------------------------------------------------------------------===//
#include <DreamReadout.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  DreamReadout dream(DreamReadout::Detector, "127.0.0.1", 9000);

  dream.setPulseTime(1, 0, 0, 0);
  dream.newPacket();
  for (int i = 0; i < 1000; i++) {
    dream.addReadout(0, 0, 1, i, 200, 11);
  }
  dream.send();

  return 0;
}
