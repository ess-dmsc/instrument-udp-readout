# Makefile for MIRACLES

# Do not edit these
INSTR=ESS_MIRACLES_v8_3
COMPS=Event_broadcaster.comp
WRAPSRC=src/wrapper.cpp src/MiraclesReadout.cpp ../common/GenericReadout.cpp
WRAPINC=src/wrapper.h src/MiraclesReadout.h ../common/GenericReadout.h
INCLUDE=-I . -I src -I ../common
LIB=libwrapper.so

# Behaviour requiring editing in Makefile
MPI=--mpi=6

# Behaviour controllable from command line
OUTPUT=		# generate files for plotting and analysis
ifeq ($(origin V), undefined)
	OUTPUT=--no-output
endif

all: $(INSTR).out

$(INSTR).out: $(LIB) $(INSTR).c
	mcrun $(MPI) -c -n 0 $(INSTR).instr

$(INSTR).c: $(INSTR).instr $(COMPS)
	mcstas $(INSTR).instr

$(LIB): $(WRAPSRC) $(WRAPINC)
	g++ --std=c++11 $(INCLUDE) $(WRAPSRC) --shared  -o $@

run: $(INSTR).out
	mcrun $(INSTR).instr $(MPI) -n 1000000000 $(OUTPUT) sendPackets=1

clean:
	rm -fr $(INSTR).c $(INSTR).out $(INSTR).out.* $(INSTR)_* $(LIB)

help:
	@echo "Setup McStas environment"
	@echo "  mcstas-3.1-environment"
	@echo "For running the simulation"
	@echo "  make run"
	@echo "Options"
	@echo "  make V=y run    # Verbose - generate data directory"
