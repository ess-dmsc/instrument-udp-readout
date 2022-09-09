include_directories(. ../common)

add_executable(bifrost
  Bifrost.cpp
  BifrostReadout.cpp
  BifrostReadout.h
  ../common/GenericReadout.cpp
  ../common/GenericReadout.h)
