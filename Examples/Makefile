CXX = clang++ 
OPT_FLAG = -O2 -march=armv8-a

CXX_FLAGS = -Wall -Werror
INCLUDE_FLAGS = -I/usr/local/include/CycleCounter/

all: SanityCheck AdditionCycles

SanityCheck: SanityCheck.cc
	$(CXX) $(OPT_FLAG) $(CXX_FLAGS) $(INCLUDE_FLAGS) SanityCheck.cc -o SanityCheck

AdditionCycles: AdditionCycles.cc
	$(CXX) $(OPT_FLAG) $(CXX_FLAGS) $(INCLUDE_FLAGS) AdditionCycles.cc -o AdditionCycles

clean: 
	rm SanityCheck AdditionCycles
