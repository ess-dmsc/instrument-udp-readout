include_directories(. ../common)

add_executable(dream
  Dream.cpp
  DreamReadout.cpp
  DreamReadout.h
  ../common/GenericReadout.cpp
  ../common/GenericReadout.h)
