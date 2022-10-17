# Makefile for MIRACLES

INSTR=ESS_MIRACLES_v8_2
COMPS=Event_broadcaster.comp
WRAPSRC=src/wrapper.cpp src/MiraclesReadout.cpp ../common/GenericReadout.cpp
WRAPINC=src/wrapper.h src/MiraclesReadout.h ../common/GenericReadout.h
INCLUDE=-I . -I src -I ../common
LIB=libwrapper.so
#MPI=--mpi=6

all: $(INSTR).out

$(INSTR).out: $(LIB) $(INSTR).c
	mcrun $(MPI) -c -n 0 $(INSTR).instr

$(INSTR).c: $(INSTR).instr $(COMPS)
	mcstas $(INSTR).instr

$(LIB): $(WRAPSRC) $(WRAPINC)
	g++ --std=c++11 $(INCLUDE) $(WRAPSRC) --shared  -o $@

run: $(INSTR).out
	mcrun $(INSTR).instr $(MPI) -n 1000000000 --no-output sendPackets=1

clean:
	rm -fr $(INSTR).c $(INSTR).out $(INSTR).out.* $(INSTR)_* $(LIB)
