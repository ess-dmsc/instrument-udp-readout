# Makefile for MIRACLES

INSTR=ESS_MIRACLES_v8_3
COMPS=Event_broadcaster.comp
WRAPSRC=src/wrapper.cpp src/MiraclesReadout.cpp ../common/GenericReadout.cpp
WRAPINC=src/wrapper.h src/MiraclesReadout.h ../common/GenericReadout.h
INCLUDE=-I . -I src -I ../common
LIB=libwrapper.so

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
LFLAGS=-fPIC --shared
else ifeq ($(UNAME), Darwin)
LFLAGS=-fPIC --shared
else
	echo "Unsupported OS"
endif


# Behaviour requiring editing in Makefile
#MPI=--mpi=6  # num of nodes
ifeq ($(origin CPU), undefined)
	MPI=
else
 	MPI=--mpi=$(CPU)
endif

# Behaviour controllable from command line
OUTPUT=		# generate files for plotting and analysis
ifeq ($(origin V), undefined)
	OUTPUT=--no-output
endif

all: $(INSTR).out

$(INSTR).out: $(LIB) $(INSTR).c
	mcrun -c $(MPI) -n 0 $(INSTR).instr

$(INSTR).c: $(INSTR).instr $(COMPS)
	mcstas $(INSTR).instr

$(LIB): $(WRAPSRC) $(WRAPINC)
	g++ --std=c++11 $(INCLUDE) $(WRAPSRC) $(LFLAGS) -o $@

run: $(INSTR).out
	mcrun $(INSTR).instr $(MPI) -n 1000000000 $(OUTPUT) sendPackets=1

clean:
	rm -fr $(INSTR).c $(INSTR).out $(INSTR).out.* $(INSTR)_* $(LIB)

help:
	@echo "Setup McStas environment"
	@echo "  mcstas-3.1-environment (or 3.2 etc.)"
	@echo "For running the simulation"
	@echo "  make run"
	@echo "Options"
	@echo "  make V=y run    # Verbose - generate data directory"
	@echo "  make CPU=n run  # use MPI in n instances"
