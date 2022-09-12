
set(CMAKE_MACOSX_RPATH OFF)

include_directories(. ../common)

# Build the demonstrator executable
add_executable(bifrost
  Bifrost.cpp
  BifrostReadout.cpp
  BifrostReadout.h
  ../common/GenericReadout.cpp
  ../common/GenericReadout.h)

# Build the McStas wrapper library
add_library(wrapper SHARED
  wrapper.cpp wrapper.h
  BifrostReadout.cpp BifrostReadout.h
  ../common/GenericReadout.cpp
  ../common/GenericReadout.h)

set_target_properties(wrapper PROPERTIES SUFFIX ".so")
set_property(TARGET wrapper PROPERTY CXX_STANDARD 11)
